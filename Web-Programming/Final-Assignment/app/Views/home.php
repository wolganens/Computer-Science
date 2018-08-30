<header>
	<div class="container">
		<div id="title" class="text-center">
			<h1>Ofereça ou contrate serviços em Alegrete.</h1>	
			<h2>Para começar, basta informar o que você procura abaixo:</h2>
			<div class="form-group">
				<select name="category" id="category-select" class="form-control">
					<option value="-1">Selecione uma categoria</option>
					<?php foreach ($categories as $category): ?>
						<option value="<?php echo $category->getId() ?>"><?php echo $category->getName() ?></option>
					<?php endforeach ?>
				</select>
			</div>	
		</div>
		<div id="client-signin-panel" class="panel panel-default hidden">
			<div class="panel-heading">
				Acesso do cliente
			</div>
			<div class="panel-body">
				<form action="index.php?controller=User&action=postSignIn" id="client-signin-form" method="POST" role="form">						
					<div class="form-group">
						<label for="client-email">Email de acesso</label>
						<input type="text" class="form-control" id="client-email" name="email" placeholder="Email de acesso">
					</div>
					<div class="form-group">
						<label for="client-password">Senha de acesso</label>
						<input type="password" class="form-control" id="client-password" name="password" placeholder="">
					</div>
					<button type="submit" class="btn btn-primary btn-block">Acessar</button>
				</form>
			</div>
			<div class="panel-footer text-center">
				<a data-toggle="modal" data-target="#new-client-modal" href="#">Criar conta</a>
			</div>
		</div>
	</div>
</header>
<section id="jobs">
	<div class="container">		
		<h3>Serviços</h3>
		<div class="row">
			<div class="col-md-4">
				<img src="public/assets/images/landing/paint-brush.svg" alt="">
				<p>Pinturas</p>
			</div>
			<div class="col-md-4">
				<img src="public/assets/images/landing/concrete-mixer.svg" alt="">
				<p>Reformas</p>
			</div>
			<div class="col-md-4">
				<img src="public/assets/images/landing/hammer.svg" alt="">
				<p>Consertos e Reparos</p>
			</div>
		</div>
		<div class="row">
			<div class="col-md-4">
				<img src="public/assets/images/landing/plug.svg" alt="">
				<p>Instalação Elétrica</p>
			</div>
			<div class="col-md-4">
				<img src="public/assets/images/landing/pipe.svg" alt="">
				<p>Encanamento</p>
			</div>
			<div class="col-md-4">
				<img src="public/assets/images/landing/screwdriver.svg" alt="">
				<p>Montador de Móveis</p>
			</div>
		</div>
	</div>
</section>
<section id="join">
	<div class="container">
		<h3>Trabalhe conosco</h3>
		<div class="row">
			<div class="col-md-6 col-md-offset-3">
				<form action="#" id="join-form" method="POST" role="form">				
					<div class="form-group">
						<label for="pro-name">Nome</label>
						<input type="text" class="form-control" id="pro-name" placeholder="Qual seu nome?">
					</div>
					<div class="form-group">
						<label for="pro-phone">Telefone</label>
						<input type="text" class="form-control" id="pro-phone" placeholder="Qual seu telefone?">
					</div>
					<div class="form-group">
						<label for="pro-description">Descreva os trabalhos que você faz</label>
						<textarea class="form-control name="" id="pro-description"></textarea>
					</div>
					<button type="submit" class="btn btn-default">Enviar</button>
				</form>
				<div id="success-join-message" class="hidden">
					<img src="public/assets/images/landing/checked.svg" class="pull-left" alt="">
					<p>
						Parabens! sua solicitação foi realizada com sucesso.
						<br/>Em breve entraremos em contato com você.
					</p>
				</div>
			</div>
		</div>
	</div>
</section>
