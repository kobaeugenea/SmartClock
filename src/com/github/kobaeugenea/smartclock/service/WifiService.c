#include "com/github/kobaeugenea/smartclock/service/WifiService.h"
#include "com/github/kobaeugenea/smartclock/service/ComponentService.h"
#include "com/github/kobaeugenea/smartclock/service/ConfigService.h"

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#define ESP_WIFI_SSID "Clock ESP"
#define ESP_WIFI_PASS ""
#define MAX_STA_CONN 1
#define ESP_MAXIMUM_RETRY 3
#define STA_SSID_MAX_LENGTH 32
#define STA_PASSWORD_MAX_LENGTH 64

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static const char *TAG = "WifiService";
static int s_retry_num = 0;

static char ssid[STA_SSID_MAX_LENGTH];
static char password[STA_PASSWORD_MAX_LENGTH];

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    //sta events
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler));
    }
    //ap events
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}

static void prepareToConnection(wifi_mode_t mode) {
    ESP_ERROR_CHECK(esp_wifi_set_mode(mode));
    if (mode == WIFI_MODE_AP || mode == WIFI_MODE_APSTA)
    {
        wifi_config_t wifiConfig = {
            .ap = {
                .ssid = ESP_WIFI_SSID,
                .ssid_len = strlen(ESP_WIFI_SSID),
                .password = ESP_WIFI_PASS,
                .max_connection = MAX_STA_CONN,
                .authmode = WIFI_AUTH_WPA_WPA2_PSK}};
        if (strlen(ESP_WIFI_PASS) == 0)
        {
            wifiConfig.ap.authmode = WIFI_AUTH_OPEN;
        }
        ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifiConfig));
    }
    if (mode == WIFI_MODE_STA || mode == WIFI_MODE_APSTA)
    {
        s_wifi_event_group = xEventGroupCreate();
        wifi_config_t wifiConfig;
        strcpy((void *)wifiConfig.sta.ssid, ssid);
        strcpy((void *)wifiConfig.sta.password, password);
        ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifiConfig));
    }
}

static void postConnection(wifi_mode_t mode)
{
    if (mode == WIFI_MODE_STA || mode == WIFI_MODE_APSTA)
    {
        /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
        EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                               WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                               pdFALSE,
                                               pdFALSE,
                                               portMAX_DELAY);

        /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
     * happened. */
        if (bits & WIFI_CONNECTED_BIT)
        {
            ESP_LOGI(TAG, "connected to ap SSID:%s password:%s", ESP_WIFI_SSID, ESP_WIFI_PASS);
        }
        else if (bits & WIFI_FAIL_BIT)
        {
            ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",ESP_WIFI_SSID, ESP_WIFI_PASS);
        }
        else
        {
            ESP_LOGE(TAG, "UNEXPECTED EVENT");
        }
        vEventGroupDelete(s_wifi_event_group);
    }
}

static void startWifi(wifi_mode_t mode) {
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL));

    prepareToConnection(mode);
    ESP_ERROR_CHECK(esp_wifi_start());

    postConnection(mode);
}

static void init()
{
    ESP_LOGI(TAG, "Initialization");
    ParamStatus ssidParamStatus = ConfigService.getNetworkSSID(ssid, STA_SSID_MAX_LENGTH);
    ParamStatus passwordParamStatus = ConfigService.getNetworkPassword(password, STA_PASSWORD_MAX_LENGTH);

    wifi_mode_t mode;
    if (ssidParamStatus == ParamStatus_ERROR ||
        ssidParamStatus == ParamStatus_EMPTY ||
        passwordParamStatus == ParamStatus_ERROR)
    {
        mode = WIFI_MODE_AP;
    } else {
        mode = WIFI_MODE_APSTA;
    }

    startWifi(mode);
    ESP_LOGI(TAG, "Initialized");
}

kea_sc_WifiService_n const kea_sc_WifiService = {
    .init = init
};

#undef ESP_WIFI_SSID
#undef ESP_WIFI_PASS
#undef MAX_STA_CONN
#undef ESP_MAXIMUM_RETRY
#undef STA_SSID_MAX_LENGTH
#undef STA_PASSWORD_MAX_LENGTH
