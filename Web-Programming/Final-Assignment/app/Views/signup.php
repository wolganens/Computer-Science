<?php use App\Views\Helpers\FormHelper;  ?>
<div id="wrapper">
	<div class="logo">
		<a href="/"><img src="public/assets/images/landing/worker.svg" alt=""><span>SG Alegrete</span></a>
	</div>
	<h1>Crie sua conta agora mesmo!</h1>
	<div id="signup">
		<form method="POST" action="index.php?controller=User&action=postCreate" id="client-signup-form">
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
			<div id="header">
				<img src="public/assets/images/landing/user.svg" alt="">
			</div>
			<div id="body">
				<?php echo FormHelper::text('Nome', 'name', NULL , ['placeholder' => 'Digite seu nome']); ?>
				<?php echo FormHelper::select('O que você procura?', 'user-type',[1 => 'Contratar serviço', 2 => 'Oferecer meus serviços'], NULL); ?>
				<div class="row">
					<div class="col-md-6">
						<?php echo FormHelper::text('Email', 'email', NULL , ['placeholder' => 'Digite seu email']); ?>
					</div>
					<div class="col-md-6">
						<?php echo FormHelper::text('Telefone', 'phone', NULL , ['placeholder' => 'Digite seu telefone']); ?>
					</div>
				</div>
				<div class="row">
					<div class="col-md-6">
						<?php echo FormHelper::password('Senha', 'password', NULL , ['placeholder' => 'Escolha uma senha']); ?>
					</div>
					<div class="col-md-6">
						<?php echo FormHelper::password('Repetir senha', 'passowrd_confirmation', NULL , ['placeholder' => 'Repita a senha']); ?>
					</div>
				</div>
			</div>
			<div id="footer">
				<div class="form-group">
					<button type="submit" class="btn-block btn-lg btn btn-primary">Concluir</button>
				</div>
				<a href="index.php?controller=Pages&action=signIn">Já tenho uma conta</a>		
			</div>
		</form>
	</div>
</div>