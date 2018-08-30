<?php

namespace App\Controllers;

use App\Models\ServiceCategory\ServiceCategoryRepository;
use App\Views\Helpers\View;

Class PagesController {	
	public function __construct() {
	}
	public function home() {
		$category_repository = new ServiceCategoryRepository();
		$categories = $category_repository->all();
		return View::render('guest', 'home', ['categories' => $categories]);
	}
	public function panel() {
		return View::render('panel', 'panel' . DIRECTORY_SEPARATOR . 'dashboard');
	}
	public function signUp() {
		return View::render('signup', 'signup');
	}
	public function signIn() {
		return View::render('signup', 'signin');
	}
}