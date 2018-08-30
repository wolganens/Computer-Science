<h1 class="page-header">Encontramos estes profissionais para seu serviço</h1>
<div class="row">
	<?php foreach ($professionals as $professional): ?>
		<div class="col-xs-12 col-sm-4 col-md-3">
			<div class="pro-card">
				<div class="header">
					<img src="public/assets/images/landing/worker.svg" alt="">
					<p> Nome: <?php echo $professional->getName(); ?><br/>Telefone: <?php echo $professional->getPhoneNumber(); ?></p>
				</div>
				<div class="body">
					<div class="clearfix">
						<p>Avaliação:</p>
						<fieldset class="rating">
						    <input type="radio" id="star5" name="rating" value="5" /><label class = "full" for="star5" title="Awesome - 5 stars"></label>
						    <input type="radio" id="star4half" name="rating" value="4 and a half" /><label class="half" for="star4half" title="Pretty good - 4.5 stars"></label>
						    <input type="radio" id="star4" name="rating" value="4" /><label class = "full" for="star4" title="Pretty good - 4 stars"></label>
						    <input type="radio" id="star3half" name="rating" value="3 and a half" /><label class="half" for="star3half" title="Meh - 3.5 stars"></label>
						    <input type="radio" id="star3" name="rating" value="3" /><label class = "full" for="star3" title="Meh - 3 stars"></label>
						    <input type="radio" id="star2half" name="rating" value="2 and a half" /><label class="half" for="star2half" title="Kinda bad - 2.5 stars"></label>
						    <input type="radio" id="star2" name="rating" value="2" /><label class = "full" for="star2" title="Kinda bad - 2 stars"></label>
						    <input type="radio" id="star1half" name="rating" value="1 and a half" /><label class="half" for="star1half" title="Meh - 1.5 stars"></label>
						    <input type="radio" id="star1" name="rating" value="1" /><label class = "full" for="star1" title="Sucks big time - 1 star"></label>
						    <input type="radio" id="starhalf" name="rating" value="half" /><label class="half" for="starhalf" title="Sucks big time - 0.5 stars"></label>
						</fieldset>
					</div>
					<form action="index.php?controller=Service&action=postConfirm" method="POST">
						<input type="hidden" name="professional" value="<?php echo $professional->getId(); ?>">
						<input type="hidden" name="category" value="<?php echo $category; ?>">
						<input type="hidden" name="address" value="<?php echo $address; ?>">
						<button type="submit" class="btn btn-primary">
							Solicitar serviço
						</button>
					</form>
				</div>
			</div>
		</div>
	<?php endforeach; ?>
</div>