<?php
include_once "include/util.inc";
include_once "models/users.inc";

function get_index($params) {
    $_SESSION = array();
    session_destroy();
    redirectRelative("index");
}
?>