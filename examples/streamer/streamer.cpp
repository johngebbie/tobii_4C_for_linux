#include <tobii/tobii.h>
#include <tobii/tobii_streams.h>
#include <stdio.h>
#include <assert.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>


using namespace std;
  
static void gaze_point_callback(tobii_gaze_point_t const *gaze_point, void *user_data) {
    if (gaze_point->validity == TOBII_VALIDITY_VALID) {
        float x = gaze_point->position_xy[0];
        float y = gaze_point->position_xy[1];
        string buffer = "g~"+to_string(x) + '~' + to_string(y) +'\n';
        const char *cstr = buffer.c_str();
        char *msg = (char *) user_data;
        strcpy(msg, cstr);
    }
}

static void url_receiver(char const *url, void *user_data) {
    char *buffer = (char *) user_data;
    if (*buffer != '\0') return; // only keep first value

    if (strlen(url) < 256)
        strcpy(buffer, url);
}

int main() {
    struct sockaddr_in server;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(9998);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t len = sizeof(server);

    char msg[256];
    char url[256];
    tobii_api_t *api;
    tobii_error_t error = tobii_api_create(&api, NULL, NULL);
    assert(error == TOBII_ERROR_NO_ERROR);

    error = tobii_enumerate_local_device_urls(api, url_receiver, url);
    assert(error == TOBII_ERROR_NO_ERROR && *url != '\0');

    tobii_device_t *device;
    error = tobii_device_create(api, url, &device);
    assert(error == TOBII_ERROR_NO_ERROR);

    error = tobii_gaze_point_subscribe(device, gaze_point_callback, msg);
    assert(error == TOBII_ERROR_NO_ERROR);

    
    while (true) {
        error = tobii_wait_for_callbacks(1, &device);
        assert(error == TOBII_ERROR_NO_ERROR || error == TOBII_ERROR_TIMED_OUT);

        error = tobii_device_process_callbacks(device);
        assert(error == TOBII_ERROR_NO_ERROR);

        sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&server, len);
    }

    error = tobii_gaze_point_unsubscribe(device);
    assert(error == TOBII_ERROR_NO_ERROR);

    error = tobii_device_destroy(device);
    assert(error == TOBII_ERROR_NO_ERROR);

    error = tobii_api_destroy(api);
    assert(error == TOBII_ERROR_NO_ERROR);
    return 0;
}