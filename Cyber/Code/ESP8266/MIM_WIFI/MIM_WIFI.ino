/*
   Captive Portal by: M. Ray Burnette 20150831
   See Notes tab for original code references and compile requirements
   Sketch uses 300,640 bytes (69%) of program storage space. Maximum is 434,160 bytes.
   Global variables use 50,732 bytes (61%) of dynamic memory, leaving 31,336 bytes for local variables. Maximum is 81,920 bytes.

   Modified by Fabrice CRASNIER for example of deviant use of the captive portal
   Cybercriminals are willing to do anything to acquire information about your uses. 
   Do not let information leak because of the automatic connections of smartphones, tablets and other connected objects. 
*/

#include <ESP8266WiFi.h>
#include "./DNSServer.h"                  // Patched lib
#include <ESP8266WebServer.h>

const byte        DNS_PORT = 53;           // Capture DNS requests on port 53
IPAddress         apIP(192, 168, 21, 1);   // Private network for server
DNSServer         dnsServer;               // Create the DNS object
ESP8266WebServer  webServer(80);           // HTTP server

String responseHTML = ""
                      "<!DOCTYPE html><html><head><title>Portail captif</title></head><body>"
                      "<h1>Merci pour vos donn&eacute;es</h1>"
"<!-- IMAGE BEGINS HERE -->"
"<font color='BLACK'>"
"<pre>                                    `.-::/+oosssyyyyyssoo+//:-.`                                    <br>"
"                               .-/+syyyyyyyyyyyyyyyyyyyyyyyyyyyyso/-.`                              <br>"
"                          `.:+syyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyo/-`                          <br>"
"                       `:+yyyyyyyyyyyyyyyyyysssooooooossyyyyyyyyyyyyyyyyyyo:.                       <br>"
"                    `:oyyyyyyyyyyyyys+/:-.-+.`         ```.-:/+syyyyyyyyyyyyyo:`                    <br>"
"                  -+yyyyyyyyyyys+:.``    :NM/                  ``.:+syyyyyyyyyyy+-                  <br>"
"               `:oyyyyyyyyyyo:.`         hMy`                       `.:+syyyyyyyyyo:`               <br>"
"             `:syyyyyyyyyo:``           .o-`         `:::::::-.`        `-+yyyyyyyyys/`             <br>"
"           `:syyyyyyyyy/.               s`         `//.     `+mms.         .:oyyyyyyyys:`           <br>"
"          .oyyyyyyyyyyy+.`             `o         -+.        `/hmy           `-oyyyyyyyyo-          <br>"
"        `:yyyyyyyyyyyyyyyyo.           `o  `  `o`-+..           .`             `.oyyyyyyyy/`        <br>"
"       `+yyyyyyys+syyyyyyyhy/`          s /s `hN.o`om-  ``                       `-syyyyyyyo`       <br>"
"      .oyyyyyyy+` ./syyyyyyyhs-    /`  `o:NN//MNs-oNMs`/h: `-             `/s.     `/yyyyyyys.      <br>"
"     .syyyyyyy:     ./yyyyyyyyy+.  ss  y/dMMNhMMNdMMMyhMM:/dy   /.     `-smNMy       -syyyyyys-     <br>"
"    .syyyyyys-        :dyyyyyyyys/.oMs.dmhMMMMMMMMMMMMMMMdMM+./yN. ``./hNms:NM--`     .syyyyyys.    <br>"
"   `syyyyyys-/o:` ` -.sy.+yyyyyyyysoNMmNMMMMMMMMMMMMMMMMMMMMdNMMd.-yhmNh/.  +Mso`` `-++:syyyyyys.   <br>"
"   +yyyyyyho+--/+/::/od+-`.+yyyyyyyyhmNMMMNdmMMMMMMMMMMd+dMMMMMNhdNMms-  `:/:sm//::+/:-/ohyyyyyyo`  <br>"
"  :yyyyyyyo-  :o+/oo./y.-/. .+yyyyyyyyhmMm- .+dNMMMMMd/` -NMMMMMMMMs.    `.  :m.:o+/+o. `:yyyyyyy/  <br>"
" `syyyyyy/  `oo.-:/oh/.+  . `-ohhyyyyyyyhs`   `ohMMms/   :NMMMMMMMMdyso+/:` .o:oy//-.:y-  /yyyyyyy. <br>"
" /yyyyyys`  +o   .sy+` :` -ymMMMNdhyyyyyyys:` .ohMMmo:.-oNMMMMMMMMMMMNdyso` /` :sh/`  .h` `syyyyyy+ <br>"
"`yyyyyyy:   +o  .d+`     .+oymMMMMNdhyyyyyyysohdysssydmMMMMMMMMMMMMMMMMNh.       -h+  .h`  -yyyyyyy`<br>"
"-yyyyyyy`    `  .s      `-+ymNMMMMMMNdyyyyyyyys:` /so``+MMMMMMMMMMmMMMm/`         -s       `syyyyyy:<br>"
"/yyyyyyo        `h   .+ydNNMMMMMMN+hMMNdyyyyyyyys:so-`-yMMMMMMNh+//MMMMNho:.``    /+        +yyyyyyo<br>"
"syyyyyy/         s`  `/yNMMMMMMMMho:sdMMNhyyyyyyyyssdNMMMMMNhoo`++hMMMMMMMMMmo.   o-        :yyyyyys<br>"
"yyyyyyy-            /mNdysyNMMMMMoss/-+omNmhyyyyyyyyhmMMmyo/  :o++sMMMMMMmy+:.    `         -yyyyyyy<br>"
"yyyyyyy-           `:. .oyhmMMMMMNy+.h:`+ `-soyyyyyyyyy/+  :+//+`hMMMMMMddhs/`              .yyyyyyy<br>"
"yyyyyyy-             .::`:ymdNMMMMMd:/.s/:-.s-:syyyyyyyys+:/o `hmMMMMMMMNdyo`               -yyyyyyy<br>"
"syyyyyy:                .-.oNMMMMMMMMm:o  `:/.::osyyyyyyyyo-yomMMMMMMMMMdy+`                :yyyyyys<br>"
"+yyyyyyo                 `++oMhhMMMMMMMMy/-/:   +`:syyyyyyyyhNMMMMMMMMMMm:                  +yyyyyy+<br>"
"-yyyyyyy`                `  y:`mMMMMMMMMMMNMNmddNmdmmhyyyyyyyhdNMMMMMMh:ym`                `syyyyyy:<br>"
"`yyyyyyy:                   . .MMMMMMMMMMMMMMMMMMMMMMMmhyyyyyyyhdNMm+Mm  :`                :yyyyyyy`<br>"
" /yyyyyys`                  -dsNMMMMNMNMMMMMMMMMMMMMMMMMmhyyyyyyyhdh/N/                   `syyyyyy+ <br>"
" `syyyyyy/                  :dMMMh/-/M+dmsMMNNMMMMMMMNMMMNyhyyyyyyyyy+.                   /yyyyyyy` <br>"
"  :yyyyyyy-               :+++MMy+: `d.+o`hMh-dMMmyNN/MMN+oy:syyyyyyyyo.                 .yyyyyyy:  <br>"
"  `oyyyyyyy.            `.-//+MN+/:  . .. `oy`.sNd :s.dy- /` :oyyyyyyyyy+.`             `syyyyyyo`  <br>"
"   `syyyyyys.        :os+//+symh+/          `   -+` ` `       ::ssyyyyyyyyys:          `oyyyyyys.   <br>"
"    .syyyyyys-      o+-.:oo/:y+``+s`                          `so./syyyyyyyhyo.       .syyyyyyy-    <br>"
"     .syyyyyyy:   `+: -s/. -h/    yy                          -M-  ./syyyyyyyhy-     -syyyyyys-     <br>"
"      .oyyyyyyy+`-s- `y-  `d/     /M-                         -M:    .+yyyyyyyyyo- `/yyyyyyys-      <br>"
"       `+yyyyyyysh-  s/   `d.     oN.                          sd.    `h+yyyyyyyyy+syyyyyyyo`       <br>"
"        `/yyyyyyyyo-`do    /h.   -m/                           `oh.   /d`.+yyyyyyyyyyyyyyy/`        <br>"
"          .oyyyyyyyy++:`    o+   ::                              --   +/   .+yyyyyyyyyyyo-          <br>"
"           `:syyyyyyyyo:`                                                  `-syyyyyyyys:`           <br>"
"             `/syyyyyyyys+.`                                            `./syyyyyyyyy/`             <br>"
"               `/syyyyyyyyys+-``                                    ``-+syyyyyyyyys/.               <br>"
"                 `:oyyyyyyyyyyyo/-.`                            ``-/oyyyyyyyyyyyo:`                 <br>"
"                    ./syyyyyyyyyyyyso+:-.`````         ````.-:/osyyyyyyyyyyyys/.                    <br>"
"                       ./oyyyyyyyyyyyyyyyyysooo++++++ooosyyyyyyyyyyyyyyyyyo/.                       <br>"
"                          `-/syyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyys+-`                          <br>"
"                              `-:+oyyyyyyyyyyyyyyyyyyyyyyyyyyyyyys+:-`                              <br>"
"                                    `.-/++osyyyyyyyyyyyyso++/:-.                                    <br>"
"</pre></font>"
"<!-- IMAGE ENDS HERE --><br><br>"
"<h2>Ce portail captif est un exemple.<br><p>Toutes les requ&ecirc;tes Web sont redirig&eacute;s ici.</p></h2><br><br>";

int compteur=0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("eduoram1");
  IPAddress myIP = WiFi.softAPIP();

  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // si le serveur DNS est démarré avec "*" pour le nom de domaine, il répondra avec IP fourni à toutes les demandes DNS
  dnsServer.start(DNS_PORT, "*", apIP);

  //Serial.println("apIP"+apIP);
  
  // Répondre à toutes les demandes de même HTML
  webServer.onNotFound([]() {
    compteur++;
    Serial.println(compteur);    
    String responseHTML_final = responseHTML + "<h1>Capture de donn&eacute;es no : "+String(compteur)+".</h1><br><br>"
                    "</body></html>";
    webServer.send(200, "text/html", responseHTML_final);
  });
  webServer.begin();
  Serial.println("Le serveur HTTP est pret");
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
  
}
