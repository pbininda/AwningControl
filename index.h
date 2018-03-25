const char HTTP_MAIN[] PROGMEM            = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><meta content=\"text/html; charset=ISO-8859-1\" http-equiv=\"content-type\"><link rel=\"shortcut icon\" type=\"image/x-icon\" href=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACMAAAAjCAMAAAApB0NrAAAAk1BMVEX///////39/f3+/v4yMjL5+ff39/fk5OQVFRMvLy84ODj29vT8/Pr6+voQEA7u7uyurqwaGhjX19Xf393w8O5JSUdeXly5ubeLi4nm5uQYGBZ6enjPz80qKio6OjrCwsAgIB5mZmRvb22ampiRkY+pqaerq6lVVVMAAAAlJSXIyMZCQkCBgX9gYF5NTUtpaWl0dHJ66DP7AAACyElEQVQ4jbVU7bKrKgwFq4iiIKBFVPy27qrdPe//dCe2nTt7Zt/78wYnJGG5EhMVIYRIii6p510Qunge+giBBcFXiJxn/yrESwH1ti8XlJLfkA/lhyF9I4H1pd5yRokHXJAHGNI3EQB+pk1fhf7wXkzez9KAAhR6F5GCI3T4W7QNG0ReXCIU6mj9OPZB3voUFzvf35swFEAV2lDXfuzf/cj5zvlRBLvv7q2L4lYpLYAoFyKsowg44Cw6F9gAjOJIRkpr4CG51rrcgbeNQVoftvZM7drY/1bW5umrcCIIIXmYkpAQ0OAJkSMbojAVr06nAETLfTBxbFa5HLLM5LWLimWNsvCf8SGinnya+2vm37ORljdamKLK6qpWgpwt987nN67tnnw2su1GXnZVbGpaZs5lIfJec/OIqL/mruWd4cU28rnpnVl4oQY+ba8+M8wS5agysmjmalAnpuBGSdfALY0+B4KDBB/0qQ4+KqhAQ0p1rSa98sm296wRJ4YlNuad3fliVzrpgZf2jxxtSa9s4qtSgAkwm+SuleyViLixV36Istpz00da93JTAkaKdcFnO/FCaMk3sdJDLNQxKysjBjpahYAnq3odfPMjN1Rqtso672hv2crHoJOVUgRhO/Bnonve5TN1IijkmOuKmnzid8Z2XochwhuFwMKpyGsaQZQOIq/4xIyUGy7l3TbILuO1UctjbLb5UStVX0tlh2Fu1GPNmu6xbgYli+Ra1H2fBwfdbVDQQeu7rLGi0rCO992GgoVzpeteWv342oX+/hpy4fihVU/LraNfpkF4urc3U/LImGe/G7PSNTO7HDrj5LEZ5wBjs9kogW+ZZuqWqUDdOs2abFOsuXU2bw7TIZZApy3OYbEEM4wZC3AgEoyxAA9f4I3E51AxTgAKVwBm8AkFYCTs/FhxcoYAcBrJiWOfHXww0//6rfw/8hezYkEUShW/dwAAAABJRU5ErkJggg==\"><title>Markise</title><style> .c { text-align:center; } input { width:55%; } input[type=\"checkbox\"] { margin-top: 3.6rem; } body { text-align:center; font-family:verdana; } button, #current-container { border:0; border-radius:0.3rem; background-color:#1fa3ec; color:#fff; line-height:2.4rem; font-size:1.2rem; width:100%; outline-style: none; margin-top: 1.2rem; margin-bottom: 1.2rem; } button.btn_on { background-color: #41ec1f; } button.btn_off { background-color: #1fa3ec; } .q { float:right; width:64px; text-align:right; } #extras.hidden { display: none; } #current-container { width: 100%; border: 2px solid #1fa3ec; background: white; box-sizing: border-box; } #current-container span { float: left; position: static; width: 100%; text-shadow: -1px -1px 10px #41ec1f, 1px -1px 10px #41ec1f, -1px 1px 10px #41ec1f, 1px 1px 10px #41ec1f; } #current-level { background: #41ec1f; height:2.4rem; transition: width 2.2s linear; } body { width: 85%; margin-left: auto; margin-right: auto; } </style><script type=\"text/javascript\"> let currentState = { state: {}, settings: {} }; let sendingState = false; let targetApi = ''; if (window.location.protocol === 'file:') { targetApi = 'http://markise'; } function onCloseClicked() { currentState.state.closeOn = true; currentState.state.openOn = false; sendState(); } function onOpenClicked() { currentState.state.openOn = true; currentState.state.closeOn = false; sendState(); } function onStopClicked() { currentState.state.closeOn = false; currentState.state.openOn = false; sendState(); } function onSetClicked() { currentState.settings.maxOnDurationMs = document.getElementById('settings_max_on_duration_ms2').value; sendState(); } function onExtrasChanged() { let el = document.querySelector('#extrascheckbox'); if (el.checked) { setClass('#extras', 'shown'); } else { setClass('#extras', 'hidden'); } } function setText(sel, text) { let el = document.querySelector(sel); el.innerHTML = text; } function setClass(sel, cls) { setAttribute(sel, 'class', cls); } function setAttribute(sel, atr, val) { let el = document.querySelector(sel); el.setAttribute(atr, val); } function handleResponse(response) { setClass('#button_open_on', response.state.openOn ? 'btn_on' : 'btn_off'); setClass('#button_close_on', response.state.closeOn ? 'btn_on' : 'btn_off'); setText('#state_open_on', response.state.openOn ? 'On' : 'Off'); setText('#state_close_on', response.state.closeOn ? 'On' : 'Off'); setText('#settings_max_on_duration_ms', response.settings.maxOnDurationMs); setAttribute('#settings_max_on_duration_ms2', 'value', response.settings.maxOnDurationMs); setText('#state_tick', response.state.tick); setText('#state_now', response.state.now); setText('#current_pos', response.state.currentPos); setText('#current-level-text', `${Math.round(response.state.currentPos / 1000)}%`); setAttribute('#current-level', 'style', `width: ${response.state.currentPos / 1000}%;`); } function sendState() { handleResponse(currentState); sendingState = true; let request = new XMLHttpRequest(); request.onreadystatechange = function() { if (request.readyState === 4) { reload(); } }; request.responseType = 'json'; request.open('POST', targetApi + '/api'); request.send(JSON.stringify(currentState)); } function reload(done) { let request = new XMLHttpRequest(); request.onreadystatechange = function() { if (request.readyState === 4) { sendingState = false; if (!sendingState) { if (request.status === 200) { currentState = request.response; handleResponse(request.response); } } if (done) { done(); } } }; request.responseType = 'json'; request.open('GET', targetApi + '/api'); request.send(); } function periodicReload() { if (!sendingState) { reload(function() { setTimeout(periodicReload, 2000); }); } else { setTimeout(periodicReload, 2000); } } periodicReload(); </script></head><body><div id=\"main\"><p><div id=\"durrent-outer\"><div id=\"current-container\"><span id=\"current-level-text\"> {{state.current_pos_pct}}% </span><div id=\"current-level\" style=\"width: {{state.current_pos_pct}}%;\"></div></div></div><button id=\"button_close_on\" onclick=\"onCloseClicked()\">Close</button><br><button id=\"button_stop\" onclick=\"onStopClicked()\">Stop</button><br><button id=\"button_open_on\" onclick=\"onOpenClicked()\">Open</button></p></div><div id=\"toggle\"><label>Extras: </label><input id=\"extrascheckbox\" onchange=\"onExtrasChanged()\" type=\"checkbox\"></div><div id=\"extras\" class=\"hidden\"><p><label>max on ms: </label><input id=\"settings_max_on_duration_ms2\" type=\"number\" min=\"0\" max=\"20000\" value=\"{{settings.max_on_duration_ms}}\"><button onclick=\"onSetClicked()\">Set</button></p><p><a href=\"/spa\">Reload</a></p><p>Opening: <span id=\"state_open_on\">{{state.open_on}}</span></p><p>Closing: <span id=\"state_close_on\">{{state.close_on}}</span></p><p>Max On: <span id=\"settings_max_on_duration_ms\">{{settings.max_on_duration_ms}}</span>ms</p><p>Tick: <span id=\"state_tick\">{{state.tick}}</span></p><p>Current: <span id=\"current_pos\">{{state.current_pos}}</span></p><p>Now: <span id=\"state_now\">{{state.now}}</span></p><p>To reset to factory defaults, load /reset</p></div></body></html>";
