#include <allegro.h>

void init();
void deinit();
void BufferTimer();
void Move();
void Reset();
void Fire();
void FireTimer();
void MoveBoss();
void FireBossTimer();
void FireBoss();
void Player_Score();
void EndGame();
void ResetTimer();

//variaveis globais
BITMAP *BackGround;
BITMAP *Buffer;
BITMAP *ScoreBuffer;
BITMAP *Witch;
BITMAP *Shoot;
BITMAP *Boss;
BITMAP *ShootBoss;
BITMAP *BackBuffer;
BITMAP *BackScoreBuffer;

SAMPLE *Music;
SAMPLE *ShootSound;

int ValMoveBoss;
int shootCount;
int ShootBossCount; 
int Score;
int Lifes = 3;
int DeadVal;

//Structs

struct witch
{
    int Top;
    int Left;
};

witch Witch_char;

struct shoot
{
    int shootX;
    int shootY;
    int Val;
};

shoot vetor_shoots[10000];

struct boss
{
    int Top;
    int Left;
};

boss bosspos;

struct BossShoot
{
    int Top;
    int Left;
    int Val;
};

BossShoot Vetor_BossShoots[10000];
BossShoot Vetor_BossShoots2[10000];
BossShoot Vetor_BossShoots3[10000];

int main() 
{ 
    init();
    
    Reset();
    
    //play_sample(Music, 180, 128, 1000, TRUE);
    
    install_int(BufferTimer, 20);
    
    install_int(Move, 3);

	install_int(FireTimer, 100);
	
	install_int(Fire, 2);
	
	install_int(MoveBoss, 10);
	
	install_int(FireBossTimer, 600);
	
	install_int(FireBoss, 15);
	
	install_int(Player_Score, 10);
	
	install_int(EndGame, 10);
	
	install_int(ResetTimer, 1);
	
    while (!key[KEY_ESC]) 
    {
         
         //o programa é baseado em Timers   
                  
	}

	deinit();
	return 0;
}
END_OF_MAIN();

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL); 
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

//Função que inseri os valores nas respectivas variaveis
void Reset()
{
    BackGround = load_bitmap("Texture/BackGround.bmp", NULL);
    draw_sprite(screen, BackGround, 0, 0);
    
    Buffer = create_bitmap(385, 448);
    
    ScoreBuffer = create_bitmap(209, 277);
	
    Witch = load_bitmap("animation/Witch/WitchBack.bmp",NULL);
    
    Shoot = load_bitmap("animation/Shoot/WitchShoot/BlueShoot.bmp", NULL);
    
    Boss = load_bitmap("animation/Boss/Boss.bmp", NULL);
    
    ShootBoss = load_bitmap("animation/Shoot/BossShoot/ShootBoss.bmp", NULL);
    
    Music = load_sample("sound/th06_14.wav");
    
    ShootSound = load_sample("sound/ShootSound.wav");
    
    BackBuffer = load_bitmap("Texture/Buffer.bmp", NULL);
    
    BackScoreBuffer = load_bitmap("Texture/ScoreBuffer.bmp", NULL);
    
    //temporario
    Witch_char.Top = 180;
    Witch_char.Left = 370;
    
    bosspos.Top = 30;
    bosspos.Left = 250;
}

//Função de movimentação/colisao/Mudança de imagens
void BufferTimer()
{
    draw_sprite(Buffer, Witch, Witch_char.Top, Witch_char.Left);
    draw_sprite(Buffer, Boss, bosspos.Left, bosspos.Top);
    draw_sprite(screen, Buffer, 32, 17);
    clear_bitmap(Buffer);
    
    draw_sprite(screen, ScoreBuffer, 423, 16);
    clear_bitmap(ScoreBuffer);
    
    draw_sprite(Buffer, BackBuffer, 0, 0); 
    draw_sprite(ScoreBuffer, BackScoreBuffer, 0, 0);
}
END_OF_FUNCTION(BufferTimer);

LOCK_FUNCTION(BufferTimer);

void Move(void)
{
        if(key[KEY_UP])
            if(Witch_char.Left>0)
            {
                Witch_char.Left--;
                Witch = load_bitmap("animation/Witch/WitchBack.bmp",NULL);
                DeadVal=0;                
            }
        if(key[KEY_DOWN])
            if(Witch_char.Left<404)
            {
                Witch_char.Left++;
                Witch = load_bitmap("animation/Witch/WitchBack.bmp",NULL);
                DeadVal=0;
            }
        if(key[KEY_RIGHT])
            if(Witch_char.Top<359)
            {
                Witch_char.Top++;
                Witch = load_bitmap("animation/Witch/WitchRight.bmp",NULL);
                DeadVal=0;
            }
        if(key[KEY_LEFT])
            if(Witch_char.Top>0)
            {
                Witch_char.Top--;
                Witch = load_bitmap("animation/Witch/WitchLeft.bmp",NULL);
                DeadVal=0;
            }
                
}
END_OF_FUNCTION(FireTimer);

LOCK_FUNCTION(FireTimer);
LOCK_VARIABLE(FireTimer);

void FireTimer(void)
{
      if(key[KEY_Z])
      {
          vetor_shoots[shootCount].shootX=Witch_char.Top+7;
          vetor_shoots[shootCount].shootY=Witch_char.Left-20;
          shootCount++;
          play_sample(ShootSound, 50, 128, 1000, FALSE);
          DeadVal=0;               
      }
}
END_OF_FUNCTION(FireTimer);

LOCK_FUNCTION(FireTimer);
LOCK_VARIABLE(FireTimer);

void Fire()
{
  if(DeadVal==0)
  {
     int loop;
     for(loop=0;loop <= shootCount;loop++)
     {
         vetor_shoots[loop].shootY--;
         if(vetor_shoots[loop].shootY > 0)
         {
             if(vetor_shoots[loop].Val==0)
             {
                 if(vetor_shoots[loop].shootY>bosspos.Top+50 || vetor_shoots[loop].shootX<bosspos.Left-5 || vetor_shoots[loop].shootX>bosspos.Left+45)
                 {
                     draw_sprite(Buffer, Shoot, vetor_shoots[loop].shootX, vetor_shoots[loop].shootY);
                 }
                 else
                 {
                     vetor_shoots[loop].Val=1;
                     Score+=100;
                 }
             }
         }
     }
  }
}
END_OF_FUNCTION(Fire);

LOCK_FUNCTION(Fire);
LOCK_VARIABLE(Fire);

void MoveBoss(void)
{
     if(ValMoveBoss==0)
     {
         bosspos.Left++;
         if(bosspos.Left+52>=385)
             ValMoveBoss=1;
     }
     if(ValMoveBoss==1)
     {
         bosspos.Left--;
         if(bosspos.Left<=0)
             ValMoveBoss=0;
     }
     
}
END_OF_FUNCTION(MoveBoss);

LOCK_FUNCTION(MoveBoss);

void FireBossTimer(void)
{
  if(DeadVal==0)
  {
     Vetor_BossShoots[ShootBossCount].Top=bosspos.Left+15;
     Vetor_BossShoots[ShootBossCount].Left=bosspos.Top+55;
     
     Vetor_BossShoots2[ShootBossCount].Top=bosspos.Left+30;
     Vetor_BossShoots2[ShootBossCount].Left=bosspos.Top+50;
     
     Vetor_BossShoots3[ShootBossCount].Top=bosspos.Left;
     Vetor_BossShoots3[ShootBossCount].Left=bosspos.Top+50;
     
     ShootBossCount++;
  }
          
}
END_OF_FUNCTION(FireBossTimer);

LOCK_FUNCTION(FireBossTimer);

void FireBoss(void)
{
  if(DeadVal==0)
  {
     int Loop;
     for(Loop=0;Loop <= ShootBossCount; Loop++)
     {
         Vetor_BossShoots[Loop].Left = Vetor_BossShoots[Loop].Left+2;
         if(Vetor_BossShoots[Loop].Top > 0)
         {
             if(Vetor_BossShoots[Loop].Val==0)
             {
                 if(Vetor_BossShoots[Loop].Left<Witch_char.Left-10 || Vetor_BossShoots[Loop].Top<Witch_char.Top-15 || Vetor_BossShoots[Loop].Top>Witch_char.Top+26 || Vetor_BossShoots[Loop].Left>Witch_char.Left+43) 
                 {
                     draw_sprite(Buffer, ShootBoss, Vetor_BossShoots[Loop].Top, Vetor_BossShoots[Loop].Left);
                 }
                 else
                 {
                     Vetor_BossShoots[Loop].Val=1;
                     
                     Lifes--;
                     
                     DeadVal=1;
                 }
             }             
         }
     } 
     
     Loop=0;
     for(Loop=0;Loop <= ShootBossCount; Loop++)
     {
         Vetor_BossShoots2[Loop].Top++;         
         if(Vetor_BossShoots2[Loop].Left > 0)
         {
            Vetor_BossShoots2[Loop].Left++;
            if(Vetor_BossShoots2[Loop].Val==0)
             {
                 if(Vetor_BossShoots2[Loop].Left<Witch_char.Left-10 || Vetor_BossShoots2[Loop].Top<Witch_char.Top-15 || Vetor_BossShoots2[Loop].Top>Witch_char.Top+26 || Vetor_BossShoots2[Loop].Left>Witch_char.Left+43) 
                 {
                     draw_sprite(Buffer, ShootBoss, Vetor_BossShoots2[Loop].Top, Vetor_BossShoots2[Loop].Left);
                 }
                 else
                 {
                     Vetor_BossShoots2[Loop].Val=1;
                     
                     Lifes--;
                     
                     DeadVal=1;
                 }
             }
         }
     }
     
     Loop=0;
     for(Loop=0;Loop <= ShootBossCount; Loop++)
     {
         Vetor_BossShoots3[Loop].Top--;
         if(Vetor_BossShoots3[Loop].Left > 0)
         {
             Vetor_BossShoots3[Loop].Left++;
             if(Vetor_BossShoots3[Loop].Val==0)
             {
                 if(Vetor_BossShoots3[Loop].Left<Witch_char.Left-10 || Vetor_BossShoots3[Loop].Top<Witch_char.Top-15 || Vetor_BossShoots3[Loop].Top>Witch_char.Top+26 || Vetor_BossShoots3[Loop].Left>Witch_char.Left+43) 
                 {
                     draw_sprite(Buffer, ShootBoss, Vetor_BossShoots3[Loop].Top, Vetor_BossShoots3[Loop].Left);
                 }
                 else
                 {
                     Vetor_BossShoots3[Loop].Val=1;
                     
                     Lifes--;
                     
                     DeadVal=1;
                 }
             }
         }
     }        
  }
}
END_OF_FUNCTION(FireBoss);

LOCK_FUNCTION(FireBoss);

void Player_Score()
{
    textprintf_ex(ScoreBuffer, font, 10, 50, makecol(225, 225, 225), -1, "Score: %d", Score);
    
    textprintf_ex(ScoreBuffer, font, 10, 80, makecol(225, 225, 225), -1, "Player: %d", Lifes);
}
END_OF_FUNCTION(Player_Score);

LOCK_FUNCTION(Player_Score);

void EndGame()
{
    if(Lifes<=0)
    {
        DeadVal=1;
        allegro_message("DERROTA");
        Lifes=3;
        Score=0;
    }
    if(Score>=10100)
    {
        DeadVal=1;
        allegro_message("VITORIA");
        Score=0;
        Lifes=3;
    }
}
END_OF_FUNCTION(EndGame);

LOCK_FUNCTION(EndGame);

void ResetTimer()
{
     if(DeadVal==1)
     {
         int Loop;
         for(Loop=0; Loop<=ShootBossCount; Loop++)
         {
             Vetor_BossShoots[Loop].Val=1;
             Vetor_BossShoots2[Loop].Val=1;
             Vetor_BossShoots3[Loop].Val=1;
         }
         
         Loop=0;
         for(Loop=0; Loop<=shootCount; Loop++)
         {
             vetor_shoots[Loop].Val=1;
         }     
         
         Witch_char.Top = 180;
         Witch_char.Left = 370;
     }     
}
END_OF_FUNCTION(EndGame);

LOCK_FUNCTION(EndGame);
