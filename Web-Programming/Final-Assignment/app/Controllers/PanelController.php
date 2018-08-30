<?php

namespace App\Controllers;

use App\Views\Helpers\View;

Class PanelController {
	public function	dashboard() {
		View::render('panel', 'panel' . DIRECTORY_SEPARATOR . 'dashboard');
	}
	public function	services() {
		View::render('panel', 'panel' . DIRECTORY_SEPARATOR . 'services');
	}
	public function	clients() {
		View::render('panel', 'panel' . DIRECTORY_SEPARATOR . 'clients');
	}
}