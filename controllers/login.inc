<?php
include_once "include/util.inc";
include_once "models/users.inc";

function safeParam($arr, $index, $default) {
    if ($arr && isset($arr[$index])) {
        return $arr[$index];
    }
    return $default;
}

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
    $username = safeParam($_REQUEST, 'email', false);
    $password = safeParam($_REQUEST, 'password', false);
    if (isValidUser($username, $password)) {
        loadUser($username);
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
            'username' => $username,
            'password' => $password
        )
    );
    // @formatter:on
    }
}
?>
