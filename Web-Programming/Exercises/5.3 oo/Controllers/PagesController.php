<?php

Class PagesController {	
	public function __construct() {		
	}
	public function home() {
		return View::render('home');
	}
}