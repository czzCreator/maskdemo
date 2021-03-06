﻿#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

/**
 * 全局截屏控件 作者:feiyangqingyun(QQ:517216493) 2016-11-11
 * 1:支持鼠标右键选择菜单
 * 2:支持全局截屏和局部截屏
 * 3:支持图片另存为
 */

#include <QWidget>
#include <QMutex>
#include <QMenu>
#include <QPoint>
#include <QSize>
#include <QDebug>

class Screen
{
public:
    enum STATUS {SELECT, MOV, SET_W_H};
    Screen() {}
    Screen(QSize size);

    void setStart(QPoint pos);
    void setEnd(QPoint pos);
    QPoint getStart();
    QPoint getEnd();

    QPoint getLeftUp();
    QPoint getRightDown();

    STATUS getStatus();
    void setStatus(STATUS status);

    int width();
    int height();
    bool isInArea(QPoint pos);          // 检测pos是否在截图区域内
    void move(QPoint p);                // 按 p 移动截图区域

private:
    QPoint leftUpPos, rightDownPos;     //记录 截图区域 左上角、右下角
    QPoint startPos, endPos;            //记录 鼠标开始位置、结束位置
    int maxWidth, maxHeight;            //记录屏幕大小
    STATUS status;                      //三个状态: 选择区域、移动区域、设置width height

    void cmpPoint(QPoint &s, QPoint &e);//比较两位置，判断左上角、右下角
};

/************************************************************/
/************************************************************/

class ScreenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenWidget(QWidget *parent = Q_NULLPTR);
    static ScreenWidget *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new ScreenWidget;
            }
        }

        return self;
    }

private:
    static ScreenWidget *self;
    QMenu *menu;            //右键菜单对象
    Screen *screen;         //截屏对象
    QPixmap *fullScreen;    //保存全屏图像
    QPixmap *bgScreen;      //模糊背景图
    QPoint movPos;          //坐标

protected:
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);

private slots:
    void initForm();
    void saveScreen();
    void saveScreenOther();
    void saveFullScreen();
};

#endif // SCREENWIDGET_H

