#include "../WebServer/App/App.h"
#include "../WebServer/Responses/HTMLResponse/HTMLResponse.h"

std::string mainPage(const HttpRequest& request) {
    return HTMLResponse::build("index.html");
}

int main() {
    App app("0.0.0.0", 8000);
    app.add_route("/", mainPage);
    app.run();
    return 1;
}