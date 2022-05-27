module tele {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens tele to javafx.fxml;
    exports tele;
}