<?php

namespace App\Controllers;

Class RequestController {
	
	private $controller;
	private $action;
	private $params;

	public function __construct($params = null) {
		$this->params = $params;		
		if (isset($_GET['controller']) && isset($_GET['action'])) {
			$this->controller = $_GET['controller'];
			$this->action = $_GET['action'];
		} else {
			$this->controller = 'Pages';
			$this->action = 'home';
		}
	}
	public function run() {
		$controller = '\App\Controllers\\' . $this->controller . 'Controller';
		$controller = new $controller();
		if (!is_null($this->params)) {
			foreach ($this->params as $key => $param) {
				$this->params[$key] = unserialize($param);
			}
		}
		$controller->{$this->action} ($this->params);
	}
    public function getController() {
        return $this->controller;
    }
    public function getAction() {
        return $this->action;
    }
}