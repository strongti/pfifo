#!/bin/bash

gnome-terminal -- /bin/sh -c 'VSOMEIP_CONFIGURATION=Image2/json/vsomeip_client.json VSOMEIP_APPLICATION_NAME=image2 ./Image2/src/image2' &

gnome-terminal -- /bin/sh -c 'VSOMEIP_CONFIGURATION=Image3/json/vsomeip_client.json VSOMEIP_APPLICATION_NAME=image3 ./Image3/src/image3' &


