<?php
include_once "include/util.inc";
include_once "models/users.inc";


function get_index($params) {
    // @formatter:off
  $_SESSION['redirect'] = safeParam($param, 1, 'index');
    renderTemplate(
        "views/login_form.inc",
        array(
            'title' => 'Login',
        )
    );
    // @formatter:on
}

function post_index($params) {
    $email = safeParam($_REQUEST, 'email', false);
    $password = safeParam($_REQUEST, 'password', false);
    if (User::isValid($email, $password)) {
        loadUser($email);
        $_SESSION['loggedin'] = true;
        if (isset($_SESSION['redirect'])) {
            $redirect = $_SESSION['redirect'];
            redirect($redirect);
            exit();
        }
        redirectRelative("index");
    } else {
    // @formatter:off
    renderTemplate(
        "views/login_form.inc",
        array(
            'title' => 'Login',
            'errors' => array("Invalid username/password"),
            'email' => $email,
            'password' => $password
        )
    );
    // @formatter:on
    }
}
?>
