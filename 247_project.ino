#include<WiFi.h>

//  To make our device as server 
#include<WebServer.h>

//  ssid , password
const char ssid[] = "Write your wifi ssid";
const char password[] = "Write your wifi password";

//  RGb led GPIOs
const byte r_pin = 25;
const byte g_pin = 26;
const byte b_pin = 27;

//  channel
const byte r_channel = 0;
const byte g_channel = 1;
const byte b_channel = 2;

//  frequency and resolution
const int frequency = 5000;
const int resolution = 8;

//  starting a server at port 80
WebServer server(80);

void setup(){

  //  setting frequency and resolution at channels
  ledcSetup(r_channel , frequency , resolution);
  ledcSetup(g_channel , frequency , resolution);
  ledcSetup(b_channel , frequency , resolution);

  //  attaching GPIOs
  ledcAttachPin(r_pin , r_channel);
  ledcAttachPin(g_pin , g_channel);
  ledcAttachPin(b_pin , b_channel);
  
  //   starting serial communication
  Serial.begin(115200);

  //  connecting with the WiFi and printing IP Address
  Serial.print("Connecting with : ");
  Serial.println(ssid);
  WiFi.begin(ssid , password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected with the Network !");
  Serial.print("IP address assgined by the access point : ");
  Serial.println(WiFi.localIP());

  //  Defining APIs
  server.on("/" , handle_root);
  server.on("/red" , handle_red);
  server.on("/green" , handle_green);

  //  if API not found


  //  start the server
  server.begin();
  Serial.println("HTTP Server started");
  
}

void loop(){
  
  //  to handle the client requests at APIs
  server.handleClient();
}

void handle_root(){
  
  Serial.println("No Color");
  //  getting html
  String html = generate_html();
  //  sending response
  server.send(200 , "text/html" , html);
}

void handle_red(){
  
  Serial.println("Red Color");
  //  getting html
  String html = generate_html();

  //  making color
  color_generator(255,0,0);
  
  //  sending response
  server.send(200 , "text/html" , html);
}

void handle_green(){

  Serial.println("Green Color");
  //  getting html
  String html = generate_html();

  //  making color
  color_generator(0,255,0);
  
  //  sending response
  server.send(200 , "text/html" , html);
}

String generate_html(){
  
  String html = "<!DOCTYPE html>\n";
         html += "<html lang=\"en\">\n";
         html += "<head>\n";
         html += "<meta charset=\"UTF-8\">\n";
         html += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
         html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
         html += "<title>ESP32 RGB CONTROLLER</title>\n";
         html += "</head>\n";
         html += "<body>\n";
         html += "<div style=\"padding-left: 50%; padding-top: 10%;\">\n";
         html += "<h1>COLOR GENERATOR</h1>\n";
         html += "</div>\n";

         html += "<div style=\"padding-left: 40%;\">\n";
         html += "<a href=\"/red\"><button>Red</button></a>\n";
         html += "<a href=\"/green\"><button>Green</button></a>\n";

                  html += "</body>\n";
         html += "</html>\n";

  return html;
}
