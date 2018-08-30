<?php

Class RequestController {
	
	private $controller;
	private $action;

	public function __construct() {
		if (isset($_GET['controller']) && isset($_GET['action'])) {
			$this->controller = $_GET['controller'];
			$this->action = $_GET['action'];
		} else {
			$this->controller = 'Pages';
			$this->action = 'home';
		}
		$this->reqController();
	}
	public function run() {		
		$controller = $this->controller . 'Controller';
		$controller = new $controller();		
		$controller->{$this->action} ();
	}

	private function reqController() {
		require_once('Controllers/' . $this->controller . 'Controller.php');
	}
    /**
     * Gets the value of controller.
     *
     * @return String
     */
    public function getController() {
        return $this->controller;
    }

    /**
     * Gets the value of action.
     *
     * @return String
     */
    public function getAction() {
        return $this->action;
    }
}