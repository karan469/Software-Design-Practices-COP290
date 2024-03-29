var display,input,input1,frames,spFrame,lvFrame,alSprite, taSprite,ciSprite,aliens,dir,tank,tank1,bullets,cities,background;
var theyHit = 0;
var weHit = 0;
var enemyCount = 0;
var mySound;
var mySound1;
var scoree;
var MainMenuImage = new Image();
inputController = new InputHandeler();
/**
 * Initiate and start the game
 */
function main() {
	
	//create game canvas and inputhandeler
	display = new Screen(504, 600)	;
	input = new InputHandeler();
	input1 = new InputHandeler();
	//create all sprites fram assets image
	var img = new Image();
	img.addEventListener("load", function() {

		alSprite = [
			[new Sprite(this,  0, 0, 22, 16), new Sprite(this,  0, 16, 22, 16)],
			[new Sprite(this, 22, 0, 16, 16), new Sprite(this, 22, 16, 16, 16)],
			[new Sprite(this, 38, 0, 24, 16), new Sprite(this, 38, 16, 24, 16)]
		];
		taSprite = new Sprite(this, 62, 0, 22, 16);
		ciSprite = new Sprite(this, 84, 8, 36, 24);

		// if(inputController.isPressed(83)){
		// 	// initate and run the game
		// 	init();
		// 	run();	
		// } else  {
		// 	runMenu();
		// }

		
		init();
		run();	
		
		
	});
	img.src = "res/invaders.png";
};

function sound(src) {
  this.sound = document.createElement("audio");
  this.sound.src = src;
  this.sound.setAttribute("preload", "auto");
  this.sound.setAttribute("controls", "none");
  this.sound.style.display = "none";
  document.body.appendChild(this.sound);
  this.play = function(){
    this.sound.play();
  }
  this.stop = function(){
    this.sound.pause();
  }
}

function init() {
	mySound = new sound("background-music.mp3");

	//starting
	frames  = 0;
	spFrame = 0;
	lvFrame = 60;

	dir = 1;

	// create the tank object
	tank = {
		sprite: taSprite,
		x: (display.width - taSprite.w) / 1.5,
		y: display.height - (30 + taSprite.h)
	};

	tank1 = {
		sprite: taSprite,
		x: (display.width - taSprite.w) / 2,
		y: display.height - (30 + taSprite.h)	
	};

	// initatie bullet array
	bullets = [];

	// create the cities object (and canvas)
	cities = {
		canvas: null,
		ctx: 	null,

		y: tank.y - (30 + ciSprite.h),
		h: ciSprite.h,

		init: function() {
			// create canvas and grab 2d context
			this.canvas = document.createElement("canvas");
			this.canvas.width = display.width;
			this.canvas.height = this.h;
			this.ctx = this.canvas.getContext("2d");

			for (var i = 0; i < 4; i++) {
				this.ctx.drawImage(ciSprite.img, ciSprite.x, ciSprite.y,
					ciSprite.w, ciSprite.h,
					68 + 111*i, 0, ciSprite.w, ciSprite.h);
			}
		},

		/**
		 * Create damage effect on city-canvas
		 * @param  {number} x x-coordinate
		 */
		generateDamage: function(x, y) {
			// round x, y position
			x = Math.floor(x/2) * 2;
			y = Math.floor(y/2) * 2;
			// draw dagame effect to canva
			this.ctx.clearRect(x-2, y-2, 4, 4);
			this.ctx.clearRect(x+2, y-4, 2, 4);
			this.ctx.clearRect(x+4, y, 2, 2);
			this.ctx.clearRect(x+2, y+2, 2, 2);
			this.ctx.clearRect(x-4, y+2, 2, 2);
			this.ctx.clearRect(x-6, y, 2, 2);
			this.ctx.clearRect(x-4, y-4, 2, 2);
			this.ctx.clearRect(x-2, y-6, 2, 2);
		},

		/**
		 * Check if pixel at (x, y) is opaque
		 * 
		 * @param  {number} x x-coordinate
		 * @param  {number} y y-coordinate
		 * @return {bool}     boolean value if pixel opaque
		 */
		hits: function(x, y) {
			// transform y value to local coordinate system
			y -= this.y;
			// get imagedata and check if opaque
			var data = this.ctx.getImageData(x, y, 1, 1);
			if (data.data[3] !== 0) {
				this.generateDamage(x, y);
				return true;
			}
			return false;
		}
	};
	cities.init(); // initiate the cities

	// create and populate alien array
	aliens = [];
	var rows = [1, 0, 0, 2, 2];
	for (var i = 0, len = rows.length; i < len; i++) {
		for (var j = 0; j < 10; j++) {
			var a = rows[i];
			// create right offseted alien and push to alien
			// array
			aliens.push({
				sprite: alSprite[a],
				x: 30 + j*30 + [0, 4, 0][a],
				y: 30 + i*30,
				w: alSprite[a][0].w,
				h: alSprite[a][0].h
			});
		}
	}
	enemyCount = aliens.length;
};


// function runMenu() {
// 	var loop = function() {
// 		renderMenu();
// 	};
// 	window.requestAnimationFrame(loop, display.canvas);
// };

/**
 * Wrapper around the game loop function, updates and renders
 * the game
 */
 var temp = 0;
var isPreviousPause = 0;
var bo = false;
function run() {
	var loop = function() {
		// console.log(isPreviousPause);
		// if(temp==0 && inputController.isPressed(65)) renderMenu();
		if(inputController.isPressed(80) || isPreviousPause == 1){	
			if(isPreviousPause==0)
			{
				renderPause();
				bo=true;
				isPreviousPause++;
			}
			if(inputController.isPressed(82) && bo==false)
			{
				isPreviousPause=0;
				mySound.stop();
				mySound = new sound("background-music.mp3");
			}
			bo=false;
			//window.requestAnimationFrame(loop, display.canvas);	
		} else if(isPreviousPause==0){
			update();
			render();
		}
		window.requestAnimationFrame(loop, display.canvas);			

	};
	window.requestAnimationFrame(loop, display.canvas);
};

function mySleep(milliseconds) {
  var start = new Date().getTime();
  for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds){
      break;
    }
  }
}; 

function resultOfEndgame(){
	if(inputController.isDown(78)){
			display.clear();
			display.ctx.fillText("You made a right choice. This is a cause not just for humanity ",20,250);
			display.ctx.fillText("but bigger. Others have a right to live peacefully too.",20,270);
			display.ctx.fillStyle = "yellow";
			display.ctx.font = "30px Arial";
			display.ctx.fillText("YOU WON IN THE ",15,360);
			display.ctx.fillText("NAME OF HUMANITY!!",15,380);
			display.ctx.fillStyle = "red";
			display.ctx.font = "20px Arial";

			if (enemyCount==0){

			} else {
				scoree = (weHit-theyHit)-(frames/1000);
			}
			
			scoree = Math.round(scoree*100)/100;
			display.ctx.fillText("Score: " + scoree, 5, 29);

		} else if (inputController.isDown(89)){
			display.clear();
			display.ctx.fillText("You made a poor choice..This is against ",30,250);
			display.ctx.fillText("our principles..This is beyond only our cause.",30,270);

			display.ctx.fillStyle = "yellow";
			display.ctx.font = "30px Arial";
			display.ctx.fillText("YOU LOST IN THE ",15,360);
			display.ctx.fillText("NAME OF HUMANITY!!",15,380);

			display.ctx.fillStyle = "red";
			display.ctx.font = "20px Arial";

			if (enemyCount==0){

			} else {
				scoree = (weHit-theyHit)-(frames/1000);
			}
			
			scoree = Math.round(scoree*100)/100;
			display.ctx.fillText("Score: " + scoree, 5, 29);
		} else {
			resultOfEndgame();
		}
};

/**
 * Update the game logic
 */
function update() {
	// if(input.isDown())
	// update the frame count
	frames++;
	
	// update tank position depending on pressed keys
	if (input.isDown(37)) { // Left
		tank.x -= 4;
	}
	if (input.isDown(39)) { // Right
		tank.x += 4;
	}
	if(input1.isDown(65)) { //Left //A Key
		tank1.x -= 4;
	}
	if(input1.isDown(68)) { //Right //D Key
		tank1.x += 4;
	}
	// keep the tank sprite inside of the canvas
	tank.x = Math.max(Math.min(tank.x, display.width - (30 + taSprite.w)), 30);
	tank1.x = Math.max(Math.min(tank1.x, display.width - (30 + taSprite.w)), 30);
	// append new bullet to the bullet array if spacebar is
	// pressed

	//in case u need it - space key is 32
	
	if (input.isPressed(87)) { // W key
		bullets.push(new Bullet(tank1.x + 10, tank1.y, -8, 2, 6, "#fff000"));
	}
	if(input.isPressed(38)){ // up key
		bullets.push(new Bullet(tank.x + 10, tank.y, -8, 2, 6, "#fff000"))
	}

	// update all bullets position and checks
	for (var i = 0, len = bullets.length; i < len; i++) {
		var b = bullets[i];
		b.update();
		// remove bullets outside of the canvas
		if (b.y + b.height < 0 || b.y > display.height) {
			bullets.splice(i, 1);
			i--;
			len--;
			continue;
		}
		// check if bullet hits any city
		var h2 = b.height * 0.5; // half hight is used for
								 // simplicity
		if (cities.y < b.y+h2 && b.y+h2 < cities.y + cities.h) {
			if (cities.hits(b.x, b.y+h2)) {
				bullets.splice(i, 1);
				i--;
				len--;
				theyHit++;
				continue;
			}
		}
		// check if bullet hit any aliens
		for (var j = 0, len2 = aliens.length; j < len2; j++) {
			var a = aliens[j];
			if (AABBIntersect(b.x, b.y, b.width, b.height, a.x, a.y, a.w, a.h)) {
				aliens.splice(j, 1);
				j--;
				len2--;
				bullets.splice(i, 1);
				i--;
				len--;
				weHit++;
				enemyCount--;
				//console.log(enemyCount);
				// increase the movement frequence of the aliens
				// when there are less of them
				switch (len2) {
					case 30: {
						this.lvFrame = 40;
						break;
					}
					case 10: {
						this.lvFrame = 20;
						break;
					}
					case 5: {
						this.lvFrame = 15;
						break;
					}
					case 1: {
						this.lvFrame = 6;
						break;
					}
				}
			}
		}
	}
	// makes the alien shoot in an random fashion 
	if (Math.random() < 0.03 && aliens.length > 0) {
		
		// mySound1 = new sound("Laser Blasts");
		// mySound1.play();

		var a = aliens[Math.round(Math.random() * (aliens.length - 1))];
		// iterate through aliens and check collision to make
		// sure only shoot from front line
		for (var i = 0, len = aliens.length; i < len; i++) {
			var b = aliens[i];

			if (AABBIntersect(a.x, a.y, a.w, 100, b.x, b.y, b.w, b.h)) {
				a = b;
			}
		}
		// create and append new bullet
		bullets.push(new Bullet(a.x + a.w*0.5, a.y + a.h, 4, 2, 4, "#f00e08"));
	}
	// update the aliens at the current movement frequence
	if (frames % lvFrame === 0) {
		spFrame = (spFrame + 1) % 2;

		var _max = 0, _min = display.width;
		// iterate through aliens and update postition
		for (var i = 0, len = aliens.length; i < len; i++) {
			var a = aliens[i];
			a.x += 30 * dir;
			// find min/max values of all aliens for direction
			// change test
			_max = Math.max(_max, a.x + a.w);
			_min = Math.min(_min, a.x);
		}
		// check if aliens should move down and change direction
		if (_max > display.width - 30 || _min < 30) {
			// mirror direction and update position
			dir *= -1;
			for (var i = 0, len = aliens.length; i < len; i++) {
				aliens[i].x += 30 * dir;
				aliens[i].y += 30;
			}
		}
	}
	//console.log(theyHit);
	if(frames>4000 && enemyCount!=0){
		display.clear();
		display.ctx.fillStyle = "yello";
		display.ctx.font = "20px Arial";
		display.ctx.fillText("We lost the war. The invaders are successful ", 30, 250);
		display.ctx.fillText("in stealing our natural resources..",30,270);
		display.ctx.fillText("specially the solar energy by using the Dyson Sphere.",30,290);
	}
	else if(enemyCount==0){
		//frames--;
		display.clear();
		display.ctx.fillStyle = "yello";
		display.ctx.font = "20px Arial";
		display.ctx.fillText("We have won!! But not entirely. This isn't the end..", 30, 250);
		//mySleep(4000);
		// display.clear();
		display.ctx.fillStyle = "yellow";
		display.ctx.font = "20px Arial";
		display.ctx.fillText("We are having two choices..", 30, 270);

		display.ctx.fillStyle = "red";
		display.ctx.font = "20px Arial";
		display.ctx.fillText("Either we let them go..Or use their advaance tech", 30, 290);
		display.ctx.fillText("to invade their planet for natural resources.",30,310);
		display.ctx.fillStyle = "yellow";
		display.ctx.fillText("What's say !?",30,330);

		display.ctx.fillStyle = "green";
		display.ctx.fillText("(Press Y to invade them..N to let them go)",30,390);

		display.ctx.fillStyle = "red";
		display.ctx.font = "20px Arial";

		if (enemyCount==0){

		} else {
			scoree = (weHit-theyHit)-(frames/1000);
		}
		
		scoree = Math.round(scoree*100)/100;
		display.ctx.fillText("Score: " + scoree, 5, 29);
		//sleep(100);
		var invade;
		// if(inputController.isDown(78)){
		// 	display.clear();
		// 	display.ctx.fillText("You made a right choice. This is a cause not just for humanity but bigger. Others have a right to live peacefully too.",30,250);
		// } else if (inputController.isDown(89)){
		// 	display.clear();
		// 	display.ctx.fillText("You made a poor choice..This is against our principles..This is beyond only our cause.",30,250);
		// } else {

		// }


		// if(invade==true){
		// 	display.clear();
		// 	display.ctx.fillStyle = "red";
		// 	display.ctx.fillText("You made a poor choice..This is against our principles..This is beyond only our cause.",30,250);
		// } else if(invade==false) {
		// 	display.clear();
		// 	display.ctx.fillStyle = "red";
		// 	display.ctx.fillText("You made a right choice. This is a cause not just for humanity but bigger. Others have a right to live peacefully too.",30,250);
		// }
		resultOfEndgame();
	}
};



function renderPause() {
	mySound.stop();
	mySleep(500);
	mySound = new sound("melodyloops.mp3");
	mySound.play();
	display.clear();
	display.ctx.fillStyle = "red";
	display.ctx.font = "20px Arial";
	display.ctx.fillText("Pause Menu", 180, 250);

	display.ctx.fillStyle = "green";
	display.ctx.font = "20px Arial";
	display.ctx.fillText("(Press R to Resume)", 150, 270);
	
	// if(inputController.isPressed(80)){
	// 	run();
	// }
	run();
};

function renderMenu() {
	//display.clear();
	mySound.stop();
	mySleep(500);
	mySound = new Sound("melodyloops.mp3");
	display.ctx.fillStyle = "red";
	display.ctx.font = "30px Arial";

	display.ctx.fillText("Main Menu", 180, 250);
	display.ctx.fillText("(Press S to start)",190,250);
	temp = 1;
	run();
};

/**
 * Render the game state to the canvas
 */
function render() {
	display.clear(); // clear the game canvas
	mySound.play();
	// background = new Image();
	// background.src = "Images/Background.png";

	// // Make sure the image is loaded first otherwise nothing will draw.
	// background.onload = function(){
	//     ctx.drawImage(background,0,0);   
	// }

	// draw all aliens
	for (var i = 0, len = aliens.length; i < len; i++) {
		var a = aliens[i];
		display.drawSprite(a.sprite[spFrame], a.x, a.y);
	}
	// save contetx and draw bullet then restore
	display.ctx.save();
	for (var i = 0, len = bullets.length; i < len; i++) {
		display.drawBullet(bullets[i]);
	}
	display.ctx.restore();
	// draw the city graphics to the canvas
	display.ctx.drawImage(cities.canvas, 0, cities.y);
	// draw the tank sprite
	display.drawSprite(tank.sprite, tank.x, tank.y);
	display.drawSprite(tank1.sprite,tank1.x,tank1.y);
	display.ctx.fillStyle = "red";
	display.ctx.font = "20px Arial";

	if (enemyCount==0){

	} else {
		scoree = (weHit-theyHit)-(frames/1000);
	}
	
	scoree = Math.round(scoree*100)/100;
	display.ctx.fillText("Score: " + scoree, 5, 29);
};

// start and run the game
//main();
