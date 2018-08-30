<?php

define('ROOT', __DIR__);
define('VIEWS', ROOT . DIRECTORY_SEPARATOR . 'Views' . DIRECTORY_SEPARATOR);

require_once('Models/User.php');
session_start();

if (is_null($_SESSION['users'])) {
	$_SESSION['users'] = [];
}

require_once('Controllers/RequestController.php');
require_once('Helpers/FormHelper.php');
require_once('Helpers/View.php');
require_once('Controllers/ValidatorController.php');

$requestController = new RequestController();

require_once('Views/layouts/guest.php');
