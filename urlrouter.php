<?php
// Utility function for handling URLs and redirecting to the correct
// controller, method_function(params) where method is get/put

// Note: If NO controller is specified, this will default to
// controllers/index.inc, to the get_index() function...

function routeUrl() {
    $method = $_SERVER['REQUEST_METHOD'];
    $requestURI = explode('/', $_SERVER['REQUEST_URI']);
    $scriptName = explode('/', $_SERVER['SCRIPT_NAME']);

    for ($i = 0; $i < sizeof($scriptName); $i++) {
        if (strtolower($requestURI[$i]) == strtolower($scriptName[$i])) {
            unset($requestURI[$i]);
        }
    }

    $command = array_values($requestURI);
    $controller = 'controllers/' . $command[0] . '.inc';
    $func = strtolower($method) . '_' . (isset($command[1]) ? $command[1] : 'index');
    $params = $method == 'POST' ? $_POST : array_slice($command, 2);

    if (file_exists($controller)) {
        require $controller;
        if (function_exists($func)) {
            $func($params);
            exit();
        }
        else {
            die("Command '$func' doesn't exist.");
        }
    } else {
        die("Controller '$controller' doesn't exist.");
    }
}
// set up session
session_set_cookie_params(60*60*24*14);
session_start();
routeUrl();
