#include "hud.h"


Hud::Hud(QWidget *parent)
  : cs::CSWidget(parent)
{
  initMember();
  initUI();
  initSignalSlot();
}

Hud::~Hud()
{

}

void Hud::initMember()
{
  _targetHeading=0;
  _heading = 0;
  _targetRoll=0;
  _roll = 0;
  _pitch = 0;
  _targetAirSpeed=0;
  _airSpeed = 0;
  _groundSpeed = 0;
  _roc = 0;
  _targetHeight=0;
  _height = 0;

  _eas = 0;
  _gs = 0;
  _amsl = 0;
  _rfh = 0;
}

void Hud::initUI()
{
  // Set attribute
  resize(400, 300);
  setWindowFlag(Qt::FramelessWindowHint);
}

void Hud::initSignalSlot()
{

}

void Hud::paintEvent(QPaintEvent *event)
{
  cs::CSWidget::paintEvent(event);

  QPainter p(this);

  drawBackground();
  drawHeading(p);
  drawRollAngle(p);
  drawPitchAngle(p);
  drawAirSpeed(p);
  drawGroundSpeed(p);
  drawRateOfClimb(p);
  drawHeight(p);

  drawLabels(p);
}

void Hud::drawBackground(){

  setAutoFillBackground(true);//必须有这条语句
  setPalette(QPalette(QColor(0,0,0)));
}

void Hud::drawHeading(QPainter &p)
{
    QSize oriSize(400, 300);
  int middleX = oriSize.width() / 2;
  p.setPen(QPen(Qt::cyan,1));

  QFontMetricsF fm(this->font());
  double w, h;
  QString scaleValue, _scaleValue;

  p.save();
  p.scale(width()/400.0, height()/300.0);
  p.translate(30, 0);

//  int middleX = width() / 2;
  //Draw a heading scale---Start
  const float space = (300 - 10) / 120.0f;
  int start=(int)qRound(_heading - 60);

  for (int i = start; i <= _heading + 60; i++) {
      double x1x2 = (space * (i - start) + 5) + 25;
      if ((int)i % 15 == 0){
          p.drawLine(x1x2, 0, x1x2, 15);

          int disp = (int)i;
          if (disp < 0){
              disp += 360;}
          disp = disp % 360;
          switch (disp) {
            case 0:
              scaleValue="N";
              break;
            case 45:
              scaleValue = "NE";
              break;
            case 90:
              scaleValue = "E";
              break;
            case 135:
              scaleValue = "SE";
              break;
            case 180:
              scaleValue = "S";
              break;
            case 225:
              scaleValue = "SW";
              break;
            case 270:
              scaleValue = "W";
              break;
            case 315:
              scaleValue = "NW";
              break;
            default:
              scaleValue = QString::number(disp % 360);
              break;
            }
          _scaleValue=QString( "%1" ).arg(scaleValue);
          w = fm.size(Qt::TextSingleLine,_scaleValue).width();
          h = fm.size(Qt::TextSingleLine,_scaleValue).height();
          p.drawText(x1x2-(w/2),30,scaleValue);
        }
      else if ((int)i % 5 == 0) {
          p.drawLine(x1x2, 0, x1x2, 10);
        }
    }
  //Draw a  heading scale---end


  //Display Target heading---Start
  QBrush bruch(Qt::SolidPattern);
  p.setPen(QPen(Qt::NoBrush,0));
  bruch.setColor(Qt::darkGray);
  p.setBrush(bruch);
  int rectX=middleX-38;
  p.drawRect(QRect(rectX, 0, 25, 18));
  p.setPen(QPen(Qt::white,1));
  _scaleValue=QString( "%1" ).arg(_targetHeading);
  w = fm.size(Qt::TextSingleLine,_scaleValue).width();
  h = fm.size(Qt::TextSingleLine,_scaleValue).height();
  p.drawText(rectX+(14.5-(w/2)),12,QString::number(_targetHeading));


  //Display Current heading---Start
  p.setPen(QPen(Qt::cyan,1));
  p.setBrush(Qt::NoBrush);
  p.drawRect(QRect(rectX, 18, 25, 18));
  p.setPen(QPen(Qt::cyan,1));
  _scaleValue=QString( "%1" ).arg(_heading);
  w = fm.size(Qt::TextSingleLine,_scaleValue).width();
  h = fm.size(Qt::TextSingleLine,_scaleValue).height();

  p.restore();
}

void Hud::drawRollAngle(QPainter &p)
{
    QSize oriSize(400, 300);

  p.save();
  p.setRenderHint(QPainter::Antialiasing,true);
  p.scale(width()/400.0, height()/300.0);

  p.translate(oriSize.width()/2, oriSize.height()/2);
  p.rotate(_roll);

  //p.scale(side / 200.0, side / 200.0);      /* 比例缩放 */
  const int m_startAngle = -60;
  const int m_endAngle = 60;
  p.drawRect(-2,-2,4,4);//中心点
  const int radius=100;
  QFontMetricsF fm(this->font());
  double w;
  QString _scaleValue;

  for(int i=m_startAngle;i<=m_endAngle;i+=5)
    {
      p.save();
      p.rotate(i);
      if(i==0){
          p.setPen(Qt::red);
        }else {
          p.setPen(Qt::cyan);
        }
      if (i % 5 == 0){
          p.drawLine(0, -radius, 0, -radius+5);
        }
      if (i % 15 == 0){
          p.drawLine(0, -radius, 0, -radius+10);
          _scaleValue=QString( "%1" ).arg(i);
          w = fm.size(Qt::TextSingleLine,_scaleValue).width();
          p.drawText(-(w/2),-radius+20, QString::number(i));
        }
      p.restore();
    }

  p.restore();
  //框注当前滚转角
  p.save();

  int middleX = oriSize.width() / 2;
  p.scale(width()/400.0, height()/300.0);

  p.translate(middleX, 70);

  QFontMetricsF fm_roll(this->font());
  double fm_roll_w;
  QString fm_roll_scaleValue;

  fm_roll_scaleValue=QString( "%1" ).arg(_roll);
  fm_roll_w = fm_roll.size(Qt::TextSingleLine,fm_roll_scaleValue).width();



  QPolygon pts;
  p.setPen(Qt::cyan);
  p.setBrush(Qt::cyan);
  pts.setPoints(3, 0,0,-5,5,5,5); //第一个参数表示3个点，后面是三个点坐标
  p.drawConvexPolygon(pts);

  p.setPen(QPen(Qt::cyan,1));
  p.setBrush(Qt::NoBrush);
  p.drawRect(QRect(-(fm_roll_w/2)-5, 5, fm_roll_w+10, 15));
  p.setPen(Qt::cyan);
  p.drawText(-(fm_roll_w/2),16,fm_roll_scaleValue);

  p.restore();
}

void Hud::drawPitchAngle(QPainter &p)
{
  p.save();
  p.setRenderHint(QPainter::Antialiasing, true);

  QFontMetricsF fm(this->font());
  double w, h;
  QString _scaleValue;
  p.translate((width() / 2), (height() / 2));
  p.scale(width()/400.0, height()/300.0);

  //p.rotate(_roll);
  int offset_x=-40;
  int offset_y=-50;
  p.drawRect(offset_x,offset_y,80,120);
  double spacing = 9;
  double every5deg = -50 / 65;
  double pitchoffset = -_pitch * every5deg;
  for (int i = 90; i >= -90; i -= 5) {
      if (i >= _pitch - 29 && i <= _pitch + 20){
          //绘制刻度线
          if(i==0){
              p.setPen(Qt::red);
            }else{
              p.setPen(Qt::cyan);
            }
          double x1=30+offset_x;
          double x2=50+offset_x;
          if (i % 2 == 0)
            {
              x1 = 20+offset_x;
              x2 = 60+offset_x;
            }
          double y1=-(pitchoffset + i * every5deg - (spacing - 19)) + 20+offset_y;
          //double y2=-(pitchoffset + i * every5deg - (spacing - 19)) + 20;
          double y2=y1;
          p.drawLine(x1,y1,x2,y2);

          //绘制刻度值
          if (i % 10 == 0){
              _scaleValue=QString( "%1" ).arg(i);
              w = fm.size(Qt::TextSingleLine,_scaleValue).width();
              h = fm.size(Qt::TextSingleLine,_scaleValue).height();
              p.drawText(x1-w,y1+(h/2),_scaleValue);
              p.drawText(x2+2,y1+(h/2),_scaleValue);
            }

          spacing += 10;
        }
    }

  // 绘制地平线
  p.restore();
  p.save();
  auto w_x_2=(width() / 2);
  auto h_y_2=(height() / 2);
  auto w_x_4=(width() / 4);
  p.translate(w_x_2, h_y_2);
  p.setPen(Qt::yellow);
  p.drawLine(-w_x_4,0,-w_x_4+15,0);
  p.drawLine(w_x_4,0,w_x_4+15,0);
  p.restore();
}

void Hud::drawAirSpeed(QPainter &p)
{
  int viewrange = 30;
  float space = (180) / (float)viewrange;//180是leftPart的高度
  int start = ((int)_airSpeed - viewrange / 2);
  QFontMetricsF fm(this->font());
  double w, h;
  QString _scaleValue;
  p.save();
  //p.setRenderHint(QPainter::Antialiasing, true);
  p.scale(width()/400.0, height()/300.0);
  p.translate(0,50);




  p.drawLine(60,0,60,180);

  p.setPen(Qt::cyan);
  for (int a = (int)start; a <= (_airSpeed + viewrange / 2); a += 1){
      double y1y2 = 180-space * (a - start);
      if (a % 5 == 0){
          p.drawLine(50, y1y2, 60, y1y2);
          _scaleValue=QString( "%1" ).arg(a);
          w = fm.size(Qt::TextSingleLine,_scaleValue).width();
          h = fm.size(Qt::TextSingleLine,_scaleValue).height();
          p.drawText(50-(w+2),y1y2+(h/2),_scaleValue);
        }
    }
  QPolygon pts;
  p.setPen(Qt::cyan);
  p.setBrush(Qt::cyan);
  pts.setPoints(3, 50,85,60,90,50,95); //第一个参数表示3个点，后面是三个点坐标
  p.drawConvexPolygon(pts);

  QFontMetricsF fm_AirSpeed(this->font()),fm_targetAirSpeed(this->font());
  double fm_AirSpeed_w,fm_targetAirSpeed_w;
  QString fm_AirSpeed_scaleValue,fm_targetAirSpeed_scaleValue;

  //框注当前空速
  fm_AirSpeed_scaleValue=QString( "%1" ).arg(_airSpeed);
  fm_AirSpeed_w = fm_AirSpeed.size(Qt::TextSingleLine,fm_AirSpeed_scaleValue).width();
  p.setPen(QPen(Qt::cyan,1));
  p.setBrush(Qt::NoBrush);
  int _AirSpeed_x=60-(fm_AirSpeed_w+10)-10;
  p.drawRect(QRect(_AirSpeed_x, 83, fm_AirSpeed_w+10, 15));

  //显示目标空速
  fm_targetAirSpeed_scaleValue=QString( "%1" ).arg(_targetAirSpeed);
  fm_targetAirSpeed_w = fm_targetAirSpeed.size(Qt::TextSingleLine,fm_targetAirSpeed_scaleValue).width();
  p.setPen(QPen(Qt::NoBrush,0));
  p.setBrush(Qt::darkGray);
  int _targetAirSpeed_x=60-(fm_AirSpeed_w+10)-10;
  p.drawRect(QRect(_targetAirSpeed_x, 68, fm_targetAirSpeed_w+10, 15));
  p.setPen(Qt::white);
  p.drawText(_targetAirSpeed_x+5,80,QString::number(_targetAirSpeed));

  p.restore();
}

void Hud::drawGroundSpeed(QPainter &p)
{

}

void Hud::drawRateOfClimb(QPainter &p)
{
    QSize oriSize(400, 300);
  const int polygonWidth = 10;//容器的宽
  const int polygonHight = 180;//容器的高
  double _verticalspeed = _roc;
  double viewrange = 12;
  _verticalspeed =std::min((viewrange / 2),_verticalspeed);
  _verticalspeed = std::max(viewrange / -2, _verticalspeed);
  double scaledvalue = _verticalspeed / -viewrange * polygonHight;
  double linespace = (float)1 / -viewrange * polygonHight;
  QPointF *points[4];
  points[0]=new QPointF(polygonWidth,polygonHight / 2);
  points[1]=new QPointF(0,polygonHight / 2);
  points[2] = points[1];
  double peak = 0;
  if (scaledvalue > 0){
      peak = -polygonWidth;
      if (180 / 2 + scaledvalue + peak < polygonHight / 2)
        {
          peak = -scaledvalue;
        }
    }else if(scaledvalue<0){
      peak = +polygonWidth;
      if (180 / 2 + scaledvalue + peak > polygonHight / 2){
          peak = -scaledvalue;
        }
    }
  points[2]=new QPointF(0,polygonHight / 2 + scaledvalue + peak);
  points[3]=new QPointF(polygonWidth,polygonHight / 2 + scaledvalue);
  //画刻度
  p.save();
  p.setRenderHint(QPainter::Antialiasing, true);

  p.scale(width()/400.0, height()/300.0);
  p.translate(oriSize.width()-65, 50);

  p.drawLine(10,0,10,180);
  for (int a = 1; a < viewrange; a++){
      p.drawLine(polygonWidth / 4,0 - linespace * a,polygonWidth,0 - linespace * a);
    }
  QVector<QPointF> *vec=new QVector<QPointF>;
  for (int i = 0; i < 4; i++){
      vec->append(*points[i]);
    }
  QPolygonF *poly=new QPolygonF(*vec);
  p.setPen(QPen(Qt::NoBrush,0));
  p.setBrush(Qt::yellow);
  p.drawPolygon(*poly);


  p.restore();
}

void Hud::drawHeight(QPainter &p)
{
    QSize oriSize(400, 300);

  p.save();
  //p.setRenderHint(QPainter::Antialiasing, true);
  p.scale(width()/400.0, height()/300.0);
  p.translate(oriSize.width()-55,50);

  QFontMetricsF fm(this->font());
  double h;
  QString _scaleValue;
  int viewrange = 30;
  float space = (180) / (float)viewrange;//180是rightPart的高度
  int start= ((int)_height - viewrange / 2);;

  for (int a =start ; a <=(_height + viewrange / 2) ; a +=1){
      double y1y2 = 180-space * (a-start);
      if (a % 5 == 0){
          p.drawLine(0,y1y2,10,y1y2);
          _scaleValue=QString( "%1" ).arg(a);
          h = fm.size(Qt::TextSingleLine,_scaleValue).height();
          p.drawText(15,y1y2+(h/2),_scaleValue);

        }else{
          p.drawLine(0,y1y2,5,y1y2);
        }
    }

  QFontMetricsF fm_Height(this->font()),fm_targetHeight(this->font());
  double fm_Height_w,fm_targetHeight_w;
  QString fm_Height_scaleValue,fm_targetHeight_scaleValue;

  //框注当前高度
  fm_Height_scaleValue=QString( "%1" ).arg(_height);
  fm_Height_w = fm_Height.size(Qt::TextSingleLine,fm_Height_scaleValue).width();
  p.setBrush(Qt::NoBrush);
  int redundancy=5;//上下浮动10m
  bool range=((_targetHeight-redundancy<_height)&&(_height<=_targetHeight+redundancy));
  range==true? p.setPen(QPen(Qt::cyan,1)):p.setPen(QPen(Qt::red,1));
  p.drawRect(10, 82, fm_Height_w+10, 18);

  QPolygon pts;
  range==true?p.setBrush(Qt::cyan):p.setBrush(Qt::red);
  pts.setPoints(3, 0,90, 10,85, 10,95); //第一个参数表示3个点，后面是三个点坐标
  p.drawConvexPolygon(pts);



  //显示目标高度
  fm_targetHeight_scaleValue=QString( "%1" ).arg(_targetHeight);
  fm_targetHeight_w = fm_targetHeight.size(Qt::TextSingleLine,fm_targetHeight_scaleValue).width();

  p.setPen(QPen(Qt::NoBrush,0));
  p.setBrush(Qt::darkGray);
  p.drawRect(QRect(10, 64, fm_targetHeight_w+10, 18));
  p.setPen(Qt::white);
  p.drawText(15,78,fm_targetHeight_scaleValue);

  p.restore();
}

void Hud::drawLabels(QPainter &p)
{
    QSize oriSize(400, 300);

  p.save();
  p.scale(width()/400.0, height()/300.0);

  p.translate(0, oriSize.height()-40);
  p.drawText(50,0,"AS:");
  p.drawText(70,0,QString::number(_airSpeed));

  p.drawText(50,15,"GS:");
  p.drawText(70,15,QString::number(_groundSpeed));
  p.restore();

  p.save();
  p.scale(width()/400.0, height()/300.0);

  QFontMetricsF fm_AMSL(this->font()),fm_RFH(this->font());
  double fm_AMSL_w,fm_AMSL_h,fm_RFH_w;
  QString fm_AMSL_scaleValue,fm_RFH_scaleValue;
  fm_AMSL_scaleValue=QString( "%1" ).arg("AMSL:");
  fm_AMSL_w = fm_AMSL.size(Qt::TextSingleLine,fm_AMSL_scaleValue).width();
  fm_AMSL_h = fm_AMSL.size(Qt::TextSingleLine,fm_AMSL_scaleValue).height();

  fm_RFH_scaleValue=QString( "%1" ).arg("RFH:");
  fm_RFH_w = fm_RFH.size(Qt::TextSingleLine,fm_RFH_scaleValue).width();

  p.translate(oriSize.width()-100, oriSize.height()-40);
  p.drawText(0,0,"AMSL:");
  p.drawText(fm_AMSL_w+10,0,QString::number(_amsl));

  double _w=fm_AMSL_w-fm_RFH_w;
  p.drawText(_w,fm_AMSL_h+3,"RFH:");
  p.drawText(fm_RFH_w+_w+10,fm_AMSL_h+3,QString::number(_rfh));

  p.restore();

}


