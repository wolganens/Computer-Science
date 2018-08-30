<?php

Class View {
	public static function render($view, $data) {
		extract($data);
		require_once(VIEWS . $view . '.php');
	}
}