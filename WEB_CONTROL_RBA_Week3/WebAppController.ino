const char *htmlHomePage PROGMEM = R"HTMLHOMEPAGE(

<!DOCTYPE html>
<html lang="th">
<head>
<meta name="viewport"
      content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no, viewport-fit=cover">

<title>Robot Arm </title>

<style>
  html, body {
    height: 100%;
    -webkit-text-size-adjust: 100%;
}
  body {
    margin: 0;
    padding: 0;
    height: 100vh;
    background: linear-gradient(120deg, white, white, white, white);
    background-size: 600% 600%;
    animation: pastelFlow 15s ease infinite;
    font-family: 'Poppins', sans-serif;
    text-align: center;
    color: #444;
    user-select: none;
    -webkit-tap-highlight-color: transparent;
    touch-action: manipulation;       /* ปิด gesture พิเศษ */
    -ms-touch-action: manipulation;   /* สำหรับ browser เก่า */
    overscroll-behavior: contain;     /* ไม่ให้เด้งหรือซูม */
    user-select: none;
  -webkit-user-select: none;
  -webkit-tap-highlight-color: transparent;
}

  @keyframes pastelFlow {
    0% { background-position: 0% 50%; }
    50% { background-position: 100% 50%; }
    100% { background-position: 0% 50%; }
  }

  h1 {
    color: black;
    text-shadow: 0 0 10px rgba(255,255,255,0.7);
    margin-top: 25px;
    letter-spacing: 1px;
    font-weight: 800;
  }

  h2 {
    color: black;
    font-weight: 400;
    font-size: 14px;
    margin-top: 4px;
  }


  /* ตารางหลักแนวนอน */
  table , td {
      margin: 45px auto;
    border-spacing: 22px;
    touch-action: none;
  }
  * {
  -webkit-touch-callout: none;     /* ไม่ให้โชว์เมนูค้างนิ้ว */
}

  td {
    width: 90px;
    height: 90px;
    border-radius: 25%;
    background: linear-gradient(145deg, white, white);
    box-shadow:
      0 6px 12px rgba(0,0,0,0.4),
      inset 0 0 5px rgba(255,255,255,0.9);
    transition: all 0.3s ease;
  }

  td:hover {
    transform: translateY(-6px) rotate(-3deg);
    box-shadow:
      0 10px 20px rgba(255,255,255,0.5),
      inset 0 0 12px rgba(255,255,255,1);
  }

  td:active {
    transform: scale(0.9);
    box-shadow:
      0 0 20px rgba(0,0,0,0.4),
      inset 0 0 15px rgba(0,0,0,9);
  }

  /* 🍯 ปุ่มกลางพิเศษ */
  .center {
    background: linear-gradient(145deg, #fff8ec, #ffe7c7);
    box-shadow:
      0 0 15px rgba(255,200,150,0.5),
      inset 0 0 8px rgba(255,255,255,0.9);
  }

  .center:hover {
    box-shadow:
      0 8px 20px rgba(255,190,130,0.7),
      inset 0 0 12px rgba(255,255,255,1);
  }

  .center:active {
    transform: scale(0.9);
    box-shadow:
      0 0 25px rgba(255,190,130,0.9),
      inset 0 0 15px rgba(255,255,255,1);
  }

  /* 🍬 ไอคอน */
  .icon {
    font-size: 42px;
    color: black;
    text-shadow: 0 0 8px rgba(255,255,255,0.6);
  }

  .center .icon {
    color: #ffb066;
    text-shadow: 0 0 8px rgba(255,190,130,0.6);
  }

  .footer {
    margin-top: 30px;
    font-size: 13px;
    color: #6b5b88;
    opacity: 0.8;
  }

  /* สำหรับจอมือถือแนวนอน */
     @media (orientation: landscape) {
     td { width: 100px; height: 100px; }
     table { border-spacing: 25px; }
  }
</style>
</head>

<body>
  <h1>Robot Arm SPSM</h1>
  <h2>5-Button Edition</h2>

  <table>
    <tr>
      <td ><span class="icon">&#8592;</span></td> 
    </tr>
  </table>
    
   <script>
    // ... (your existing JavaScript code)
      var webSocketUrl = "ws:\/\/" + window.location.hostname + "/ws";
      var websocket;
      
      function initWebSocket() 
      {
        websocket = new WebSocket(webSocketUrl);
        websocket.onopen    = function(event){};
        websocket.onclose   = function(event){setTimeout(initWebSocket, 2000);};
        websocket.onmessage = function(event){};
      }

      function onTouchStartAndEnd(value) 
      {
        websocket.send(value);
      }
  
     function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/" + x, true);
     xhr.send();
    }
            
    window.onload = initWebSocket;
      document.getElementById("mainTable").addEventListener("touchend", function(event)       {
        event.preventDefault()
    
    (function () {
  var iOS = /iP(ad|hone|od)/.test(navigator.userAgent);
  if (!iOS) return;

  // กัน pinch-zoom
  document.addEventListener('touchmove', function (e) {
    if (e.scale !== undefined && e.scale !== 1) {
      e.preventDefault();
    }
  }, { passive: false });

  // กัน gesture ซูม 3 นิ้วของ Safari
  ['gesturestart','gesturechange','gestureend'].forEach(function(evt){
    document.addEventListener(evt, function(e){ e.preventDefault(); }, { passive: false });
  });

  // กัน double-tap zoom (แตะติดกัน 300ms)
  var lastTouch = 0;
  document.addEventListener('touchend', function (e) {
    var now = Date.now();
    if (now - lastTouch <= 10) {
      e.preventDefault();
    }
    lastTouch = now;
  }, true);
})();
      });

    </script>
  </body>
</html>

)HTMLHOMEPAGE";
void handleRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", htmlHomePage);

  // Send web page to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", htmlHomePage);
  });

  // Recevie
  server.on("/TURN_RIGHT_RM", HTTP_GET, [](AsyncWebServerRequest *request) {
    hold_flag = "TURN_RIGHT_RM";
    Serial.println(hold_flag);
    request->send(200, "text/plain", "ok");
  });
  server.on("/TURN_LEFT_RM", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(hold_flag);
    hold_flag = "TURN_LEFT_RM";
    request->send(200, "text/plain", "ok");
  });
  server.on("/EXTEND", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(hold_flag);
    hold_flag = "EXTEND";
    request->send(200, "text/plain", "ok");
  });
  server.on("/RESTACK", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(hold_flag);
    hold_flag = "RESTACK";
    request->send(200, "text/plain", "ok");
  });
  server.on("/UPPER", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(hold_flag);
    hold_flag = "UPPER";
    request->send(200, "text/plain", "ok");
  });
  server.on("/LOWER", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(hold_flag);
    hold_flag = "LOWER";
    request->send(200, "text/plain", "ok");
  });
  server.on("/UPPER_G", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(hold_flag);
    hold_flag = "UPPER_G";
    request->send(200, "text/plain", "ok");
  });
  server.on("/LOWER_G", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(hold_flag);
    hold_flag = "LOWER_G";
    request->send(200, "text/plain", "ok");
  });
  server.on("/GRIP", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(hold_flag);
    hold_flag = "GRIP";
    request->send(200, "text/plain", "ok");
  });
  server.on("/UN_GRIP", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(hold_flag);
    hold_flag = "UN_GRIP";
    request->send(200, "text/plain", "ok");
  });
  server.on("/home", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(hold_flag);
    hold_flag = "home";
    request->send(200, "text/plain", "ok");
  });
  server.on("/H_OFF", HTTP_GET, [](AsyncWebServerRequest *request) {
    hold_flag = "H_OFF";
    Serial.println(hold_flag);
    request->send(200, "text/plain", "ok");
  });
}

void handleNotFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "File Not Found");
}

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      // client->text(getRelayPinsStatusJson(ALL_RELAY_PINS_INDEX));
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      
      break;
    case WS_EVT_DATA:
      AwsFrameInfo *info;
      info = (AwsFrameInfo *)arg;
      if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        std::string myData = "";
        myData.assign((char *)data, len);
        // Serial.println(myData.c_str());
      }
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
    default:
      break;
  }
}
