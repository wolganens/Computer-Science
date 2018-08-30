<!DOCTYPE html>
<html lang="pt-BR">
	<head>
		<meta charset="utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<title>Serviços Gerais - Alegrete</title>
		<link href="https://fonts.googleapis.com/css?family=Lato:300,300i,400,700|Open+Sans:300,400,400i,600,700|Roboto:300,400,700" rel="stylesheet"> 
		<link rel="stylesheet" href="public/assets/css/panel.css">
		<link rel="stylesheet" href="public/assets/images/panel/flaticon.css">
		<link rel="stylesheet" href="//netdna.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css">
		<!--[if lt IE 9]>
			<script src="https://oss.maxcdn.com/libs/html5shiv/3.7.2/html5shiv.min.js"></script>
			<script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
		<![endif]-->
	</head>
	<body>
	<div class="modal fade" id="map-modal">
		<div class="modal-dialog">
			<div class="modal-content">
				<div class="modal-header">
					<button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
					<h4 class="modal-title">Endereço do serviço</h4>
				</div>
				<div class="modal-body">
					<div id="map"></div>
				</div>
				<div class="modal-footer">
					<button type="button" class="btn btn-default" data-dismiss="modal">Fechar</button>
				</div>
			</div>
		</div>
	</div>
	<div id="map"></div>
	<nav class="navbar navbar-default navbar-fixed-top" role="navigation">
		<div class="container-fluid">
			<div class="navbar-header">
				<button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-ex1-collapse">
					<span class="sr-only">Toggle navigation</span>
					<span class="icon-bar"></span>
					<span class="icon-bar"></span>
					<span class="icon-bar"></span>
				</button>
			</div>
	
			<!-- Collect the nav links, forms, and other content for toggling -->
			<div class="collapse navbar-collapse navbar-ex1-collapse">
				<ul class="nav navbar-nav navbar-right">
					<li class="dropdown">
						<a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">
							<?php echo $user->getName(); ?> 
							<span class="caret"></span>
						</a>
						<ul class="dropdown-menu">
							<li><a href="index.php?controller=User&action=getProfile">Meus dados</a></li>							
							<li><a href="index.php?controller=User&action=getSignOut">Sair</a></li>
						</ul>
					</li>
				</ul>
			</div><!-- /.navbar-collapse -->
		</div>
	</nav>	
	<aside>
		<div id="header">
			<div class="logo">
				<a href="/" title="Página inicial"><img src="public/assets/images/landing/worker.svg" alt=""></a>
			</div>
		</div>		
