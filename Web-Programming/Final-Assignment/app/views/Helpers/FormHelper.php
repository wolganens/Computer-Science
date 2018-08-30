<?php

namespace App\Views\Helpers;

Class FormHelper {
	public function construct() {
	}
	public static function text($label, $name, $value = null, $options = null) {		
		$id = isset($options['id']) ? $options['id'] : $name;
		
		if (isset($_SESSION['errors'][$name])) {
			$error = sprintf('<div class="alert alert-danger">%s</div>', $_SESSION['errors'][$name]);
		} else {
			$error = '';
		}
		
		return sprintf(
			'<div class="form-group">
				<label for="%s">%s</label>
				<input type="text" class="form-control" id="%s" name="%s" value="%s" placeholder="%s">
				%s
			</div>',
			$id, $label, $id, $name, $value, isset($options['placeholder']) ? $options['placeholder'] : null, $error
		);
	}
	public static function select($label, $name, $option_array = null , $value = null, $options = null) {		
		$id = isset($options['id']) ? $options['id'] : $name;
		$options_html = '';

		if (isset($_SESSION['errors'][$name])) {
			$error = sprintf('<div class="alert alert-danger">%s</div>', $_SESSION['errors'][$name]);
		} else {
			$error = '';
		}
		if (!is_null($option_array)) {
			foreach ($option_array as $key => $value) {
				$options_html.= sprintf('<option value="%s">%s</option>', $key, $value);
			}
		}
		return sprintf(
			'<div class="form-group">
				<label for="%s">%s</label>
				<select class="form-control" id="%s" name="%s" value="%s" placeholder="%s">%s</select>
				%s
			</div>',
			$id, $label, $id, $name, $value, isset($options['placeholder']) ? $options['placeholder'] : null, $options_html, $error
		);
	}
	public static function password($label, $name, $options = null) {
		$id = isset($options['id']) ? $options['id'] : $name;
		if (isset($_SESSION['errors'][$name])) {
			$error = sprintf('<div class="alert alert-danger">%s</div>', $_SESSION['errors'][$name]);
		} else {
			$error = '';
		}
		return sprintf(
			'<div class="form-group">
				<label for="%s">%s</label>
				<input type="password" class="form-control" id="%s" name="%s" placeholder="%s">
				%s
			</div>',
			$id, $label, $id, $name, isset($options['placeholder']) ? $options['placeholder'] : null, $error
		);
	}
	public static function submit($text, $class = '') {
		return sprintf('<button type="submit" class="btn btn-primary %s">%s</button>', $class, $text);
	}
}