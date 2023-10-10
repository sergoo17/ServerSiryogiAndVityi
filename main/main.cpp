#include "../WebServer/App/App.h"
#include "../WebServer/Responses/HTMLResponse/HTMLResponse.h"

std::string mainPage(const HttpRequest& request) {
    return HTMLResponse::build("index.html");
}
std::string game(const HttpRequest& request) {

    return HTMLResponse::build("game.html");
}
int main() {
    App app("0.0.0.0", 8000);
    app.router.add_route("/", mainPage);
    app.router.add_route("/game", game);
    app.run();
    return 1;
}