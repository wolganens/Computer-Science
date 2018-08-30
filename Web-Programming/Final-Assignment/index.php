<?php

define('ROOT', __DIR__);
define('VIEWS', ROOT . DIRECTORY_SEPARATOR . 'App' . DIRECTORY_SEPARATOR . 'Views' . DIRECTORY_SEPARATOR);
session_start();
/**
  * Autoload do composer para carregar as classes
  */ 
require_once __DIR__.'/vendor/autoload.php';
/**
 * Controladora para gerenciar as requisições
 */
use App\Controllers\RequestController;
/**
 * Classe para conexão com banco de dados
 */
use App\Models\Db;
/**
 * Classes auxiliares para utilização nas Views
 */
use App\Views\Helpers\FormHelper;
use App\Views\Helpers\View;
/**
 * Inicio do controle de requisições
 */
$request = new RequestController($_SESSION['params'] ?? null);
$request->run();