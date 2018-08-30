<?php

namespace App\Views\Helpers;

use App\Models\User\Auth;

Class View {
	public static function render($layout, $view, $data = null) {
		if (!is_null($data)) {
			extract($data);
		}
		$success = $_SESSION['success'] ?? null;
		$user = Auth::user() ?? null;
		$danger = $_SESSION['danger'] ?? null;
		unset($_SESSION['success']);
		unset($_SESSION['danger']);
		ob_start();
		include(VIEWS . $view . '.php');
		$content = ob_get_contents();
		ob_end_clean();
		require_once(VIEWS . 'layouts' . DIRECTORY_SEPARATOR . $layout . DIRECTORY_SEPARATOR . $layout . '.php');
	}
	public static function getHeader($layout)
	{
		include(VIEWS . 'layouts' . DIRECTORY_SEPARATOR . $layout . DIRECTORY_SEPARATOR . 'header.php');
	}
	public static function getFooter($layout)
	{
		include(VIEWS . 'layouts' . DIRECTORY_SEPARATOR . $layout . DIRECTORY_SEPARATOR . 'footer.php');
	}
}