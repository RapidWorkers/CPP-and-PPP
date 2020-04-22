#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include "ui_ConvFilter_GUI.h"
#include "ConvFilters.h"

class ConvFilter_GUI : public QMainWindow
{
	Q_OBJECT

public:
	ConvFilter_GUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::ConvFilter_GUIClass ui;
	Filtering filter;
	QPixmap orig;
	QPixmap mod;
	QImage filtered;

public slots:
	void openImage() {
		QString target = QFileDialog::getOpenFileName(this, "Open Image", "./", "Images (*.bmp; *.png; *.jpg);;ALL files (*.*)");
		if (!target.isNull() && !target.isEmpty()) {
			orig.load(target);
			int w = ui.label->width();
			int h = ui.label->height();

			ui.label->setPixmap(orig.scaled(w, h, Qt::KeepAspectRatio));
			ui.label_3->setPixmap(orig.scaled(w, h, Qt::KeepAspectRatio));

			filtered = orig.toImage();
		}
	};

	void bBlur() { applyFilter(ConvFilters::FILT_BOX_BLUR); }
	void gBlur() { applyFilter(ConvFilters::FILT_GAU_BLUR); }
	void eLight() { applyFilter(ConvFilters::FILT_EDGE_LIGHT); }
	void eHeavy() { applyFilter(ConvFilters::FILT_EDGE_HEAVY); }
	void eMedium() { applyFilter(ConvFilters::FILT_EDGE_MEDIUM); }

	void resetImg() {
		int w = ui.label->width();
		int h = ui.label->height();
		ui.label->setPixmap(orig.scaled(w, h, Qt::KeepAspectRatio));
		ui.label_3->setPixmap(orig.scaled(w, h, Qt::KeepAspectRatio));
		filtered = orig.toImage();
	}

	void poolImg() {
		vector<unsigned char> R, G, B;
		vector<unsigned char> Rn, Gn, Bn;

		int neww, newh;

		if (filtered.width() == 1 || filtered.height() == 1) return;

		for (int i = 0; i < filtered.width(); i++)
			for (int j = 0; j < filtered.height(); j++) {
				QRgb px = filtered.pixel(i, j);
				R.push_back(qRed(px));
				G.push_back(qGreen(px));
				B.push_back(qBlue(px));
			}
		filter.maxPool2x2(R, Rn, filtered.width(), filtered.height(), neww, newh);
		filter.maxPool2x2(G, Gn, filtered.width(), filtered.height(), neww, newh);
		filter.maxPool2x2(B, Bn, filtered.width(), filtered.height(), neww, newh);

		filtered = filtered.scaled(neww, newh);

		for (int i = 0; i < neww; i++)
			for (int j = 0; j < newh; j++) {
				QRgb value = qRgb(Rn[i*neww + j], Gn[i*neww + j], Bn[i*neww + j]);
				filtered.setPixel(i, j, value);
			}

		mod = mod.fromImage(filtered);
		int w = ui.label_3->width();
		int h = ui.label_3->height();
		ui.label_3->setPixmap(mod.scaled(w, h, Qt::KeepAspectRatio));

	}

	void applyFilter(ConvFilters type) {
		vector<unsigned char> R, G, B;
		vector<unsigned char> Rn, Gn, Bn;

		for(int i = 0; i < filtered.width(); i++)
			for (int j = 0; j < filtered.height(); j++) {
				QRgb px = filtered.pixel(i, j);
				R.push_back(qRed(px));
				G.push_back(qGreen(px));
				B.push_back(qBlue(px));
			}
		filter.apply(R, Rn, filtered.width(), filtered.height(), type);
		filter.apply(G, Gn, filtered.width(), filtered.height(), type);
		filter.apply(B, Bn, filtered.width(), filtered.height(), type);


		for (int i = 0; i < filtered.width(); i++)
			for (int j = 0; j < filtered.height(); j++) {
				QRgb value = qRgb(Rn[i*filtered.width() + j], Gn[i*filtered.width() + j], Bn[i*filtered.width() + j]);
				//QRgb value = qRgb(R[i*filtered.width() + j], G[i*filtered.width() + j], B[i*filtered.width() + j]);
				filtered.setPixel(i, j, value);
			}

		mod = mod.fromImage(filtered);
		int w = ui.label_3->width();
		int h = ui.label_3->height();
		ui.label_3->setPixmap(mod.scaled(w, h, Qt::KeepAspectRatio));
		

	};
};
