<?php
require_once('header.php');
echo '<div id="content">' . (isset($danger) ? '<div class="alert alert-danger">' . $danger .'</div>' : '' . isset($success) ? '<div class="alert alert-success"> ' . $success  . '</div>' : '') . $content . '</div>' ;
require_once('footer.php');