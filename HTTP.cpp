#include <ESP8266WebServer.h>
#include "HTTP.h"
#include "state.h"
#include "persistence.h"

ESP8266WebServer server(80);
bool serverSetupDone = false;
const uint8 NUM_MODES = 10;

#define TITEL "Markise"

String head() {
  return "<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<meta content=\"text/html; charset=ISO-8859-1\" http-equiv=\"content-type\">\r\n<title>" TITEL "</title>\r\n</hread>\r\n<body>\r\n";
}

String tail() {
  return "</body>\r\n</html>\r\n";
}

void sendResult(String &resp) {
  server.send(200, "text/html", resp);
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


void handleSet() {
  extractArgs();
  sendResult(head() + formBody() + statusBody() + "<p>sent command</p>\r\n" + tail());
}


void initServer() {
  // Start the server
  server.on("/", HTTP_GET, handleIndex);
  server.on("/", HTTP_POST, handleSet);
  server.on("/switch", HTTP_GET, handleSet);
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

