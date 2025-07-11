/*
    ------ WIFI Example --------
 
    Explanation: This example shows how to configure the WiFi module
    to join a specific Access Point. So, ESSID and password must be
    defined.
 
    Copyright (C) 2021 Libelium Comunicaciones Distribuidas S.L.
http://www.libelium.com
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
    Version:           3.0
    Implementation:    Yuri Carmona
*/
 
#include <WaspWIFI_PRO_V3.h>
 
 
// choose socket (SELECT USER'S SOCKET)
///////////////////////////////////////
uint8_t socket = SOCKET0;
///////////////////////////////////////
 
// WiFi AP settings (CHANGE TO USER'S AP)
///////////////////////////////////////
char SSID[] = "LANCOMBEIA";
char PASSW[] = "beialancom";
///////////////////////////////////////
 
// define variables
uint8_t error;
uint8_t status;
unsigned long previous;
 
 
void setup()
{
  USB.println(F("Start program"));
 
  //////////////////////////////////////////////////
  // 1. Switch ON the WiFi module
  //////////////////////////////////////////////////
  error = WIFI_PRO_V3.ON(socket);
 
  if (error == 0)
  {
    USB.println(F("1. WiFi switched ON"));
  }
  else
  {
    USB.println(F("1. WiFi did not initialize correctly"));
  }
 
 
  //////////////////////////////////////////////////
  // 2. Reset to default values
  //////////////////////////////////////////////////
  error = WIFI_PRO_V3.resetValues();
 
  if (error == 0)
  {
    USB.println(F("2. WiFi reset to default"));
  }
  else
  {
    USB.print(F("2. WiFi reset to default error: "));
    USB.println(error, DEC);
  }
 
  //////////////////////////////////////////////////
  // 3. Configure mode (Station or AP)
  //////////////////////////////////////////////////
  error = WIFI_PRO_V3.configureMode(WaspWIFI_v3::MODE_STATION);
 
  if (error == 0)
  {
    USB.println(F("3. WiFi configured OK"));
  }
  else
  {
    USB.print(F("3. WiFi configured error: "));
    USB.println(error, DEC);
  }
 
  // get current time
  previous = millis();
 
 
  //////////////////////////////////////////////////
  // 4. Configure SSID and password and autoconnect
  //////////////////////////////////////////////////
  error = WIFI_PRO_V3.configureStation(SSID, PASSW, WaspWIFI_v3::AUTOCONNECT_ENABLED);
 
  if (error == 0)
  {
    USB.println(F("4. WiFi configured SSID OK"));
  }
  else
  {
    USB.print(F("4. WiFi configured SSID error: "));
    USB.println(error, DEC);
  }
 
 
  if (error == 0)
  {
    USB.println(F("5. WiFi connected to AP OK"));
 
    USB.print(F("SSID: "));
    USB.println(WIFI_PRO_V3._essid);
    USB.print(F("Channel: "));
    USB.println(WIFI_PRO_V3._channel, DEC);
 
    USB.print(F("Signal strength: "));
    USB.print(WIFI_PRO_V3._power, DEC);
    USB.println("dB");
 
    USB.print(F("IP address: "));
    USB.println(WIFI_PRO_V3._ip);
 
    USB.print(F("GW address: "));
    USB.println(WIFI_PRO_V3._gw);
 
    USB.print(F("Netmask address: "));
    USB.println(WIFI_PRO_V3._netmask);
 
    WIFI_PRO_V3.getMAC();
 
    USB.print(F("MAC address: "));
    USB.println(WIFI_PRO_V3._mac);
  }
  else
  {
    USB.print(F("5. WiFi connect error: "));
    USB.println(error, DEC);
 
    USB.print(F("Disconnect status: "));
    USB.println(WIFI_PRO_V3._status, DEC);
 
    USB.print(F("Disconnect reason: "));
    USB.println(WIFI_PRO_V3._reason, DEC);
 
    /*
      enum ConnectionFailureReason{
        REASON_INTERNAL_FAILURE = 1,
        REASON_AUTH_NO_LONGER_VALID = 2,
        REASON_DEAUTH_STATION_LEAVING = 3,
        REASON_DISASSOCIATED_INACTIVITY = 4,
        REASON_DISASSOCIATED_AP_HANDLE_ERROR = 5,
        REASON_PACKET_RECEIVED_FROM_NONAUTH_STATION = 6,
        REASON_PACKET_RECEIVED_FROM_NONASSOC_STATION = 7,
        REASON_DISASSOCIATED_STATION_LEAVING = 8,
        REASON_STATION_REQUEST_REASSOC = 9,
        REASON_DISASSOCIATED_PWR_CAPABILITY_UNACCEPTABLE = 10,
        REASON_DISASSOCIATED_SUPPORTED_CHANNEL_UNACCEPTABLE = 11,
        REASON_INVALID_ELEMENT = 13,
        REASON_MIC_FAILURE = 14,
        REASON_FOUR_WAY_HANDSHAKE_TIMEOUT = 15,
        REASON_GROUP_KEY_HANDSHAKE_TIMEOUT = 16,
        REASON_ELEMENT_IN_FOUR_WAY_HANDSHAKE_DIFFERENT = 17,
        REASON_INVALID_GROUP_CIPHER = 18,
        REASON_INVALID_PAIRWISE_CIPHER = 19,
        REASON_AKMP = 20,
        REASON_UNSUPPORTED_RSNE_CAPABILITIES = 21,
        REASON_INVALID_RSNE_CAPABILITIES = 22,
        REASON_IEEE_AUTH_FAILED = 23,
        REASON_CIPHER_SUITE_REJECTED = 24,
        REASON_STATION_LOST_BEACONS_CONTINUOUSLY = 200,
        REASON_STATION_FAILED_TO_SCAN_TARGET_AP = 201,
        REASON_STATION_AUTH_FAILED_NOT_TIMEOUT = 202,
        REASON_STATION_AUTH_FAILED_NOT_TIMEOUT_NOT_MANY_STATIONS = 203,
        REASON_HANDHASKE_FAILED = 204,
      };
    */
  }
}
 
 
void loop()
{
 
  // Check if module is connected
  if (WIFI_PRO_V3.isConnected() == true)
  {
    USB.print(F("WiFi is connected OK"));
    USB.print(F(" Time(ms):"));
    USB.println(millis() - previous);
 
    USB.println(F("\n*** Program stops ***"));
    while (1)
    {}
  }
  else
  {
    USB.print(F("WiFi is connected ERROR"));
    USB.print(F(" Time(ms):"));
    USB.println(millis() - previous);
  }
 
  delay(10000);
 
}
