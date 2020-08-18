void handleSendPage() {
    String nick = "", color = "", text = "";
    for (uint8_t i = 0; i < server.args(); i++) {
        if (server.argName(i) == "nick") {
            nick = server.arg(i);
        } else if (server.argName(i) == "color") {
            color = server.arg(i);
        } else if (server.argName(i) == "text") {
            text = server.arg(i);
        }
    }

    if (nick != "", color != "", text != "") {
        addMessage(nick, color, text);
        server.send(200, "text/plain", "OK");
    } else {
        server.send(400, "text/plain", "Something went wrong!");
    }
}
