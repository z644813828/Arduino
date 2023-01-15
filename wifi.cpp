#include "display.h"
#include "led.h"
#include "mqtt.h"
#include "soil_wetness.h"
#include "wifi.h"

#include "secrets.h"

Wifi::Wifi()
    : m_server(80)
{
}

Wifi &Wifi::Instance()
{
    static Wifi instance;
    return instance;
}

void Wifi::setup()
{
    Serial.println();
    for (int i = 0; i < WiFi.scanNetworks(); i++)
        Serial.println(WiFi.SSID(i));

    delay(2000);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.hostname("Name");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void Wifi::InitHandler()
{
    m_server.on("/", [&]() {
        // clang-format off
        String str = R"(
<style>
	body {
		background-color: black !important;
	}

	.data {
		background-image: url('https://phonoteka.org/uploads/posts/2021-05/1621343517_4-phonoteka_org-p-igrovoi-fon-asus-5.jpg') !important;
		background-repeat: no-repeat;
		background-attachment: local;
		background-position: right;
		background-size: cover;
		color: white;
	}

	h1 {
		color: white;
	}

	div {
		color: white;
	}


	.toggle.ios,
	.toggle-on.ios,
	.toggle-off.ios {
		border-radius: 20px;
	}

	.toggle.ios .toggle-handle {
		border-radius: 20px;
	}

	#content {
		margin: auto;
		left: 1%;
		right: 1%;
		position: absolute;
	}
</style>
<html lang="en">
<head>
	<title>Arduino Control Page</title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">

	<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
	<script src="https://code.jquery.com/jquery-3.6.3.min.js" integrity="sha256-pvPw+upLPUjgMXY0G+8O0xUf+/Im1MZjXxxgOcBQBXU=" crossorigin="anonymous"></script>
	<script src="https://cdn.jsdelivr.net/npm/bootstrap5-toggle@5.0.4/js/bootstrap5-toggle.jquery.min.js"></script>

	<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
	<link href="https://cdn.jsdelivr.net/npm/bootstrap5-toggle@5.0.4/css/bootstrap5-toggle.min.css" rel="stylesheet" />
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
</head>

<body>
    <h1 class="mx-4">Arduino Control Page</h1>
	<div class="row w-100 mx-2">
		<div class="d-none d-md-block col-3"> </div>
		<div class="col-12 col-md-3">
			<div>
				<div>Theme</div>
				<form class="d-flex" action="/get">
					<button class="btn btn-light" type="submit">Set</button>
					<select class="form-control mx-2" id="color" name="color">
                        )" + Led::Instance().getHtmlColors() + R"(
                    </select>
				</form>
			</div>
			<div>
				<div>Brightness</div>
				<form class="form-group d-flex" action="/get">
					<button class="btn btn-light" type="submit">Set</button>
					<input type="range" class="form-control-range mx-2 flex-fill" id="brightness" name="brightness" min="0" max="255"
                        value= ")" + Led::Instance().getBrightness() + R"("
                        step="5">
					<label id="brightness_label">)" + Led::Instance().getBrightness() + R"(</label>
				</form>
			</div>
			<div>
				<div>Effect</div>
				<form class="d-flex" action="/get">
					<button class="btn btn-light" type="submit">Set</button>
					<select class="form-control mx-2" id="effect" name="effect">
                        )" + Led::Instance().getHtmlEffects() + R"(
                    </select>
				</form>
			</div>
			<div>
				<div>Error Effect</div>
				<form class="d-flex" action="/get">
					<button class="btn btn-light" type="submit">Set</button>
					<select class="form-select mx-2" id="error_effect" name="error_effect">
                        )" + Led::Instance().getHtmlErrorEffects() + R"(
                    </select>
				</form>
			</div>
		</div>
		<div class="col-12 col-md-3">
			<div>Effect arguments</div>
            )" + Led::Instance().getHtmlArguments() + R"(
            <br>
			<div>Debug LED strip</div>
			<form class="d-flex" action="/get">
				<button class="btn btn-success" type="submit">Set</button>
				<div class="mx-2">
					<input type="hidden" name="debug_led" id="debug_led"/>
					<input type="checkbox" data-toggle="toggle"
                        )" + (Led::Instance().getDebug() ? "checked" : "") + R"(
						data-onlabel="<i class='fa fa-play'></i> Start"
						data-offlabel="<i class='fa fa-pause'></i> Stop"
						data-onstyle="danger" id="debug_led_toggle">
				</div>
			</form>
			<br>
			<br>
			<div>Other settings</div>
            <form class="d-flex" action="/get">
                <button class="btn btn-light" type="submit">Set</button>
                <div class="input-group mx-2">
                    <div class="input-group-prepend">
                        <span class="input-group-text" id="basic-addon1">SoilWetness</span>
                    </div>
                    <input type="text" class="form-control" aria-describedby="basic-addon1"
                        name="soil_wetness" placeholder=")" + String(SoilWetness::Instance().getDrySignal()) + R"(">
                </div>
            </form>
			<form class="d-flex" action="/get">
				<button class="btn btn-info" type="submit">Start display test</button>
				<input type="hidden" id="debug_led" name="display_test" value="0"/>
			</form>
		</div>
	</div>
</body>
</html>

<script type="text/javascript">
$("#brightness").on("change", function() {
	$("#brightness_label").text($(this).val());
})
$('#debug_led_toggle').change(function() {
     $('#debug_led').val($(this).prop('checked') ? "1" : "0")
})
$('#debug_led').val($('#debug_led_toggle').prop('checked') ? "1" : "0")
</script>
        )";
        // clang-format on

        m_server.send(200, "text/html", str);
    });

    m_server.on("/get", [&]() {
        String arg;

        if ((arg = m_server.arg(HTTP_REQUEST_COLOR)) != "") {
            Led::Instance().setColor(arg);
            Mqtt::Instance().set(String(MQTT_LED_COLOR_TOPIC), arg);
        }

        if ((arg = m_server.arg(HTTP_REQUEST_EFFECT)) != "") {
            Led::Instance().setEffect(arg);
        }

        if ((arg = m_server.arg(HTTP_REQUEST_ERROR_EFFECT)) != "") {
            Led::Instance().setErrorEffect(arg);
        }

        if ((arg = m_server.arg(HTTP_REQUEST_BRIGHTNESS)) != "") {
            Led::Instance().setBrightness(arg.toInt());
        }

        if ((arg = m_server.arg(HTTP_REQUEST_SOIL_WETNESS)) != "") {
            SoilWetness::Instance().setDrySignal(arg.toInt());
        }

        if ((arg = m_server.arg(HTTP_REQUEST_LED_DEBUG)) != "") {
            Led::Instance().setDebug(arg.toInt());
        }

        if ((arg = m_server.arg(HTTP_REQUEST_DISPLAY_TEST)) != "") {
            Display::Instance().startSelfTest();
        }

        for (int i = 0; i < 10; i++) {
            String param = HTTP_REQUEST_EFFECT_ARG + String(i);
            if ((arg = m_server.arg(param)) != "")
                Led::Instance().setEffectArg(i, arg);
        }

        m_server.sendHeader("Location", "/", true);
        m_server.send(302, "text/plain", "");
    });
}

void Wifi::loop()
{
    bool new_status = WiFi.status() == WL_CONNECTED;

    if (new_status != m_wifiStatus) {
        if (new_status) {
            Serial.println("WiFi Connected");
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
            InitHandler();
            m_server.begin();
        } else {
            Serial.println("WiFi Disconnected");
        }
    }

    m_wifiStatus = new_status;
    Display::Instance().setWifiConnected(m_wifiStatus);

    m_server.handleClient();
}
