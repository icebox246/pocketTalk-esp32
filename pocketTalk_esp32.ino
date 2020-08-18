// simple chat server for off-grid low distance communication

#include <DNSServer.h>
#include <WebServer.h>
#include <WiFi.h>

// Set you Acces Point parameters here
const char* ssid = "pocketTalk";
const char* password = "........";

#define MAX_MESS_NUM 100

#define DNS_PORT 53
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
WebServer server(80);

// structure to store messages
struct Message {
    String nick = "", color = "FFFFFF", text = "";
};

Message messages[MAX_MESS_NUM];
int currentTail = 0;

void addMessage(String nick, String color, String text) {
    messages[currentTail].nick = nick;
    messages[currentTail].color = color;
    messages[currentTail].text = text;

    currentTail = (currentTail + 1) % MAX_MESS_NUM;
}

void setup() {
    // Setting up serial for debugging
    Serial.begin(9600);
    Serial.println("");

    // Setting up acces point
    WiFi.mode(WIFI_AP);
    //  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid, password);

    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    dnsServer.start(byte(DNS_PORT), "pocket.talk", apIP);

    addMessage("[SERVER]", "FF0000", "Just woke up ;)");

    server.on("/", handleRootPage);
    server.on("/messages", handleMessagesPage);
    server.on("/send", handleSendPage);

    //  server.onNotFound(handleNotFound);

    server.begin();

    Serial.println("HTTP server started!");
}

void loop() {
    dnsServer.processNextRequest();
    server.handleClient();
}
