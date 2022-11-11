String rootPage = "";

void handleRootPage() {
    if (rootPage.length() == 0) {
        rootPage = readWholeTextFile("/index.html");
    }

    server.send(200, "text/html", rootPage.c_str());
}
