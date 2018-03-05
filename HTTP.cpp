#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "HTTP.h"
#include "state.h"
#include "persistence.h"
#include "index.h"


ESP8266WebServer server(80);
bool serverSetupDone = false;
const uint8 NUM_MODES = 10;

#define TITEL "Markise"

const char HTTP_HEAD1[] PROGMEM = "<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n<meta content=\"text/html; charset=ISO-8859-1\" http-equiv=\"content-type\">\r\n<title>" TITEL "</title>\r\n";
const char HTTP_STYLE[] PROGMEM = "<style> .c{text-align:center;}div,input{padding:5px;font-size:1em;}input{width:55%;}body{text-align:center;font-family:verdana;}button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float:right;width:64px;text-align:right;} </style>";;
const char HTTP_HEAD2[] PROGMEM = "</hread>\r\n<body>\r\n";

String head() {
  return String(HTTP_HEAD1) + String(HTTP_STYLE) + String(HTTP_HEAD2);
}

const char HTTP_TAIL[] PROGMEM = "<p><a href=\"/reset\">Reset</a></p> </body>\r\n</html>\r\n";

String tail() {
return String(HTTP_TAIL);
}

void sendResult(String &resp) {
  server.send(200, "text/html", resp);
}

void sendJsonResult(String resp) {
  server.send(200, "application/json", resp);
}

String statusBody() {
  String res("");
  res += "<p>Opening: " + String(state.open_on) + "</p>";
  res += "<p>Closing: " + String(state.close_on) + "</p>";
  res += "<p>Max On:  " + String(settings.max_on_duration_ms) + "ms</p>";
  res += "<p>Tick: " + String(state.tick) + "</p>";
  res += "<p>Now:  " + String(state.now) + "</p>";
  return res;
}


String numInput(const char *label, const char *name, long min, long max, int value) {
  return String("<label>") + label + ":</label><input name=\"" + name + "\" type=\"number\" min=\"" + String(min) + " \" max=\"" + String(max) + "\" value=\"" + String(value) + "\"></p>";
}

String boolInput(const char *label, const char *name, bool value) {
  return String("<label>") + label + ":</label><input name=\"" + name + "\" type=\"checkbox\" "+ (value ? "\"checked\"" : "") + "></p>";
}


String formBody() {
  String res("<form action=\"/\" method=\"post\">");
  res += String("<p>") + boolInput("Open On", "open", state.open_on) + "</p>";
  res += String("<p>") + boolInput("Close On", "close", state.close_on) + "</p>";
  res += String("<p>") + numInput("max on ms", "maxon", 0, 20000, settings.max_on_duration_ms) + "</p>";
  res +=         "<button type=\"submit\">Set</button>";
  res +=     "</form>\r\n";
  res += "<p><a href=\"/\">Reload</a></p>";
  return res;
}

bool extractArgBool(const char *arg, bool &target) {
  String str = server.arg(arg);
  if (str.length() > 0) {
    target = str == "on";
    return true;
  }
  return false;
}

bool extractArg8(const char *arg, uint8_t &target) {
  String str = server.arg(arg);
  if (str.length() > 0) {
    target = str.toInt();
    return true;
  }
  return false;
}

bool extractArg16(const char *arg, uint16_t &target) {
  String str = server.arg(arg);
  if (str.length() > 0) {
    target = str.toInt();
    return true;
  }
  return false;
}

bool extractArg32(const char *arg, uint32_t &target) {
  String str = server.arg(arg);
  if (str.length() > 0) {
    target = str.toInt();
    return true;
  }
  return false;
}

void extractArgs() {
  extractArg32("maxon", settings.max_on_duration_ms);
  bool open;
  if (extractArgBool("open", open)) {
    if (open) {
      trigger_open(0);
    }
    else {
      cancel_open();
    }
  }
  bool close;
  if (extractArgBool("close", close)) {
    if (close) {
      trigger_close(0);
    }
    else {
      cancel_close();
    }
  }
  writeSettings();
}

void handleIndex() {
  extractArgs();
  sendResult(head() + formBody() + statusBody() + tail());
}

String index() {
  String res(HTTP_MAIN);
  res.replace("{{?state.open_on?}}", state.open_on ? "\"checked\"" : "");
  res.replace("{{?state.close_on?}}", state.close_on ? "\"checked\"" : "");
  res.replace("{{state.open_on}}", state.open_on ? "on" : "off");
  res.replace("{{state.close_on}}", state.close_on ? "on" : "off");
  res.replace("{{settings.max_on_duration_ms}}", String(settings.max_on_duration_ms));
  res.replace("{{state.tick}}", String(state.tick));
  res.replace("{{state.now}}", String(state.now));
  return res;
}

void handleSpa() {
  extractArgs();
  String indexData = index();
  sendResult(indexData);
}

void handleSet() {
  extractArgs();
  sendResult(head() + formBody() + statusBody() + "<p>sent command</p>\r\n" + tail());
}

void handleReset() {
  sendResult(head() + formBody() + statusBody() + "<p>reset started</p>\r\n" + tail());
  clearSettings();
  ESP.eraseConfig();
  ESP.reset();  
}

void handleApiGet() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject &jsRoot = jsonBuffer.createObject();
  JsonObject &jsState = jsRoot.createNestedObject("state");  
  JsonObject &jsSettings = jsRoot.createNestedObject("settings");  
  jsState["openOn"] = state.open_on;
  jsState["closeOn"] = state.close_on;
  jsState["tick"] = state.tick;
  jsState["now"] = state.now;
  jsSettings["maxOnDurationMs"] = settings.max_on_duration_ms;
  String jsonString;
  jsRoot.printTo(jsonString);
  // Serial.println(jsonString);
  sendJsonResult(jsonString);
}

void handleApiPost() {
  DynamicJsonBuffer jsonBuffer;
  String jsonString(server.arg("plain"));
  // Serial.print("POST: ");
  // Serial.println(jsonString);
  JsonObject &root = jsonBuffer.parseObject(jsonString);
  if (root.success()) {
    Serial.println("root success");
    JsonObject &jsState = root["state"];
    JsonObject &jsSettings = root["settings"];
    if (jsState["closeOn"]) {
      trigger_close(0);
    }
    else if (jsState["openOn"]) {
      trigger_open(0);
    }
    else {
      cancel_open();
      cancel_close();
    }
    uint32_t maxOn = jsSettings["maxOnDurationMs"];
    if (maxOn != 0) {
      settings.max_on_duration_ms = maxOn;
    }
  }
  sendJsonResult("\"OK\"");
}

void initServer() {
  // Start the server
  server.on("/", HTTP_GET, handleIndex);
  server.on("/spa", HTTP_GET, handleSpa);
  server.on("/api", HTTP_GET, handleApiGet);
  server.on("/api", HTTP_POST, handleApiPost);
  server.on("/", HTTP_POST, handleSet);
  server.on("/switch", HTTP_GET, handleSet);
  server.on("/reset", HTTP_GET, handleReset);
  server.begin();
  serverSetupDone = true;
  Serial.print("Server started on ");
  Serial.println(WiFi.localIP());
}

void handleServer() {
  if (serverSetupDone) {
      server.handleClient();
  }
}

