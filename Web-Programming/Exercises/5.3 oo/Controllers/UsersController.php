<?php

Class UsersController {
	public function postCreate() {
		$user = new User(
			$_POST['name'],
			$_POST['cpf'],
			$_POST['date'],
			$_POST['email'],
			$_POST['password']
		);
		if (!empty($_SESSION['errors'])) {
			return View::render('home');
		}
		$user->save();
		return View::render('users', ['users' => $_SESSION['users']]);
	}
}