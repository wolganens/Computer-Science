<!DOCTYPE html>
<html lang="pt-BR">
	<head>
		<meta charset="utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<title>Serviços Gerais - Alegrete</title>
		<link href="https://fonts.googleapis.com/css?family=Lato:300,300i,400,700|Open+Sans:300,400,400i,600,700|Roboto:300,400,700" rel="stylesheet"> 
		<link rel="stylesheet" href="public/assets/css/landing.css">
		<!--[if lt IE 9]>
			<script src="https://oss.maxcdn.com/libs/html5shiv/3.7.2/html5shiv.min.js"></script>
			<script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
		<![endif]-->
	</head>
	<body>
		<nav class="navbar navbar-default navbar-fixed-top" role="navigation">
			<div class="container-fluid container">
				<div class="navbar-header">
					<button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-ex1-collapse">
						<span class="sr-only">Toggle navigation</span>
						<span class="icon-bar"></span>
						<span class="icon-bar"></span>
						<span class="icon-bar"></span>
					</button>
					<a class="navbar-brand" href="/">
						<img src="public/assets/images/landing/worker.svg" alt=""><span>SG Alegrete</span>
					</a>
				</div>
		
				<!-- Collect the nav links, forms, and other content for toggling -->
				<div class="collapse navbar-collapse navbar-ex1-collapse">
					<ul class="nav navbar-nav navbar-right">
						<li class="active">
							<a href="#">Contratar serviços</a>
						</li>
						<li>
							<a href="#join">Oferecer serviços</a>
						</li>
						<li>
							<a href="index.php?controller=Pages&action=signup" class="text-success"><strong>Cadastro</strong></a>
						</li>
						<li>
							<a href="index.php?controller=Pages&action=signin" class="text-primary"><strong>Entrar</strong></a>
						</li>
					</ul>
				</div><!-- /.navbar-collapse -->
			</div>
		</nav>
		<?php if (isset($danger)): ?>
			<div class="alert alert-danger">
				<?php echo $danger ?>
			</div>
		<?php endif ?>
		<?php if (isset($success)): ?>
			<div class="alert alert-success">
				<?php echo $success ?>		
			</div>
		<?php endif ?>	
