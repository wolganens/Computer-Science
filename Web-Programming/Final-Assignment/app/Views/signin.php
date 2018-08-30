<?php use App\Views\Helpers\FormHelper;  ?>
<div id="wrapper">
	<div class="logo">
		<a href="/"><img src="public/assets/images/landing/worker.svg" alt=""><span>SG Alegrete</span></a>
	</div>
	<h1>Utilize seus dados de acesso:</h1>
	<div id="signup">
		<form method="POST" action="index.php?controller=User&action=postSignIn" id="client-signup-form">
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
				<?php echo FormHelper::text('Email', 'email', NULL , ['placeholder' => 'Email de acesso']); ?>
				<?php echo FormHelper::password('Senha', 'password', NULL , ['placeholder' => 'Senha de acesso']); ?>
			</div>
			<div id="footer">
				<div class="form-group">
					<button type="submit" class="btn-block btn-lg btn btn-primary">Acessar</button>
				</div>
				<p>
					<a href="index.php?controller=Pages&action=signUp">Criar uma conta</a>
				</p>
				<p>
					<a href="index.php?controller=Pages&action=rememberPassword">Esqueci minha senha</a>
				</p>
			</div>
		</form>
	</div>
</div>