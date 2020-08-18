void handleMessagesPage() {
    String message = "";

    for (int i = MAX_MESS_NUM; i > 0; i--) {
        int currentIndex = (currentTail - i + MAX_MESS_NUM) % MAX_MESS_NUM;
        message += messages[currentIndex].nick + '\t' + messages[currentIndex].color + '\t' + messages[currentIndex].text + '\n';
    }

    server.send(200, "text/plain", message);
}
