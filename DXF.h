#ifndef DXF_H
#define DXF_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "StdAfx.h"
using namespace std;
class point
{
public:
	double x,y;
	point(){x=0;y=0;}
	point(double loc_x,double loc_y){x=loc_x;y=loc_y;}
	void operator=(point& p){x=p.x;y=p.y;return;}
};

class DXF
{
public:
	//自定參數
	string file_name;
	//HEADER_SECTION
	double LIMMIN_10,LIMMIN_20,LIMMAX_10,LIMMAX_20;
	
	double LTSCALE,DIMSCALE,DIMASZ,DIMEXO,DIMEXE,DIMDLI,DIMRND,DIMDLE,DIMTP,DIMTM;
	double DIMTXT,DIMCEN,DIMTSZ,DIMALTF,DIMLFAC,DIMTVP,DIMTFAC,DIMGAP;//140~147

	unsigned DIMTOL,DIMLIM,DIMTIH,DIMTOH,DIMSE1,DIMSE2,DIMTAD,DIMZIN;//71~78
	unsigned DIMALT,DIMALTD,DIMTOFL,DIMSAH,DIMTIX,DIMSOXD,DIMCLRD,DIMCLRE,DIMCLRT;//170~178

	string DIMBLK,TEXTSTYLE,DIMSTYLE;

	unsigned LUNITS,LUPREC,COORDS;

protected:
	//低階
	void draw_line(ofstream& fout, point i, point j, string LAYER_NAME = "0", string LINE_TYPE = "BYLAYER", unsigned color = 256)  const;
	void draw_polyline(ofstream& fout, point i,vector<point> points, string LAYER_NAME = "0", string LINE_TYPE = "BYLAYER", unsigned color = 256,unsigned poly_type =0,double starting_width = 0,double end_width = 0)  const;
	void draw_lwpolyline(ofstream& fout, point i,vector<point> points, string LAYER_NAME = "0", string LINE_TYPE = "BYLAYER", unsigned color = 256,unsigned poly_type = 1,double starting_width = 0,double end_width = 0)  const;
	void draw_vertex(ofstream& fout, point i, string LAYER_NAME = "0", string LINE_TYPE = "BYLAYER", unsigned color = 256,double starting_width = 0,double end_width = 0, double bulge=0, unsigned flags = 1, double curve_fit_tangent_angle =0)  const;
	void draw_text(ofstream& fout, point i,point j,string content ,string style,double text_hight , string LAYER_NAME, string LINE_TYPE,
		unsigned color = 256,double relative_X_scale =1.0,double oblique_angle = 0.0,double rotation =0, unsigned generation_flags =0,
		unsigned horizontal_text_justification_type =1,unsigned vertical_text_justification_type =2) const;
	void insert_block(ofstream& fout, string block_name, point i,double x_scale_factor =1,double y_scale_factor =1, double rotation = 0, string LAYER_NAME = "0", string LINE_TYPE = "BYLAYER", unsigned color = 256) const;
	void draw_arc(ofstream& fout, point center,double radius, double start_angle, double end_angle, string LAYER_NAME = "0", string LINE_TYPE = "BYLAYER", unsigned color = 256)  const;
	void draw_dimension(ofstream& fout,point i,point j,point p13,point p14,string LAYER_NAME = "DIMS",string LINE_TYPE = "BYLAYER",unsigned color = 256,string BLOCK_NAME = "*D0",string STYLE_NAME = "AT",string DRAW_TYPE = "<>") const;

	void draw_polyline_start(ofstream& fout, point i, string LAYER_NAME = "0", string LINE_TYPE = "BYLAYER", unsigned color = 256,unsigned poly_type =0,double starting_width = 0,double end_width = 0)  const;
	void draw_polyline_end(ofstream& fout, point i, string LAYER_NAME = "0", string LINE_TYPE = "BYLAYER", unsigned color = 256,unsigned poly_type =0,double starting_width = 0,double end_width = 0)  const;
public:
	DXF();

	virtual void fout();
	virtual void fout_header(ofstream& fout) const;
	virtual void fout_classes(ofstream& fout) const;
	virtual void fout_tables(ofstream& fout) const;
	virtual void fout_blocks(ofstream& fout) const;
	virtual void fout_entities(ofstream& fout) const;
	virtual void fout_objects(ofstream& fout) const;
	virtual void fout_thumbnailimage(ofstream& fout) const;
};

class beam_col
{
public:
	double bay_length;
	double CITEM_1_1_upper_W,CITEM_1_2_lower_W,CITEM_1_3_jbeam_W;
	double CITEM_2_1_upper_offset,CITEM_2_2_lower_offset,CITEM_2_3_jbeam_offset;

};
class beam_bay
{
public:
	string bay_ID;
	double BITEM_1_1_W,BITEM_1_2_D,BITEM_1_3_offset;
	unsigned BITEM_2_1_size,BITEM_2_2_i_first_line,BITEM_2_3_m_first_line,BITEM_2_4_j_first_line;
	unsigned BITEM_3_1_size,BITEM_3_2_i_second_line,BITEM_3_3_m_second_line,BITEM_3_4_j_second_line;
	unsigned BITEM_4_1_size,BITEM_4_2_i_third_line,BITEM_4_3_m_third_line,BITEM_4_4_j_third_line;
	unsigned BITEM_5_1_size,BITEM_5_2_i_fourth_line,BITEM_5_3_m_fourth_line,BITEM_5_4_j_fourth_line;
	unsigned BITEM_6_1_i_shear,BITEM_6_2_i_shear_size,BITEM_6_3_i_shear_dis;
	unsigned BITEM_6_4_m_shear,BITEM_6_5_m_shear_size,BITEM_6_6_m_shear_dis;
	unsigned BITEM_6_7_j_shear,BITEM_6_8_j_shear_size,BITEM_6_9_j_shear_dis;
	unsigned BITEM_7_1_EF_size,BITEM_7_2_EF;

public:
	void modify_BITEM_2_2_i_first_line(unsigned n){BITEM_2_2_i_first_line = n;}
	void modify_BITEM_2_3_m_first_line(unsigned n){BITEM_2_3_m_first_line = n;}
	void modify_BITEM_2_4_j_first_line(unsigned n){BITEM_2_4_j_first_line = n;}
	void modify_BITEM_3_2_i_second_line(unsigned n){BITEM_3_2_i_second_line = n;}
	void modify_BITEM_3_3_m_second_line(unsigned n){BITEM_3_3_m_second_line = n;}
	void modify_BITEM_3_4_j_second_line(unsigned n){BITEM_3_4_j_second_line = n;}
	void modify_BITEM_4_2_i_third_line(unsigned n){BITEM_4_2_i_third_line = n;}
	void modify_BITEM_4_3_m_third_line(unsigned n){BITEM_4_3_m_third_line = n;}
	void modify_BITEM_4_4_j_third_line(unsigned n){BITEM_4_4_j_third_line = n;}
	void modify_BITEM_5_2_i_fourth_line(unsigned n){BITEM_5_2_i_fourth_line = n;}
	void modify_BITEM_5_3_m_fourth_line(unsigned n){BITEM_5_3_m_fourth_line = n;}
	void modify_BITEM_5_4_j_fourth_line(unsigned n){BITEM_5_4_j_fourth_line = n;}

};
class beam
{
public:
	string FL;
	vector<beam_col> cols;
	vector<beam_bay> beams;

public:
	beam();
	beam(const beam& b);
	beam(string FL,vector<beam_col> cols,vector<beam_bay> beams);

public:
	unsigned page;
	double loc_x,loc_y,x_end;

};
class BEAM_DXF : public DXF
{
public:
	vector<beam> beam_dat;
	unsigned total_pages;
public:

	virtual void fout_tables(ofstream& fout) const;
	virtual void fout_blocks(ofstream& fout) const;
	virtual void fout_entities(ofstream& fout) const;

public:
	//中階
	void beam_length_modify();
	void draw_canvas(ofstream& fout, point left_down, point right_up)  const;
	void draw_beam(ofstream& fout,point page_left_up, const beam& b)  const;

	//輔助
	void draw_breakLine(ofstream& fout,point p1,point p2,string LAYER_NAME = "OLINE", string LINE_TYPE = "BYLAYER", unsigned color = 256) const;
	void typesetting();

public:
	//資料
	void clear();
};

class column
{
public:
	string FL,ID;
public:
	double ITEM_1_1_W,ITEM_1_2_D;
	unsigned ITEM_2_1_CornerSteelSize, ITEM_2_2_CornerSteel,ITEM_2_3_CornerSteel;
	unsigned ITEM_3_1_SteelSize, ITEM_3_2_X_Steel,ITEM_3_3_Y_Steel;
	unsigned ITEM_6_1_HookSteel, ITEM_6_2_HookSteelSize,ITEM_6_3_HookSteelDistance;
	unsigned ITEM_7_1_HookSteel, ITEM_7_2_HookSteelSize,ITEM_7_3_HookSteelDistance,ITEM_7_4_HookSteelDistance2;
	unsigned ITEM_8_1_TieSteelSize, ITEM_8_2_X_TieSteel,ITEM_8_3_Y_TieSteel;
	unsigned ITEM_9_1_CornerDoubleSteelSize, ITEM_9_2_X_CornerDoubleSteel,ITEM_9_3_Y_CornerDoubleSteel;
	unsigned ITEM_10_1_CornerDoubleSteelSize, ITEM_10_2_X_CornerDoubleSteel,ITEM_10_3_Y_CornerDoubleSteel;
public:
	column();
	column(double ITEM_1_1_W,double ITEM_1_2_D,unsigned ITEM_2_1_CornerSteelSize,unsigned ITEM_2_2_CornerSteel,unsigned ITEM_2_3_CornerSteel,
			 unsigned ITEM_3_1_SteelSize,unsigned ITEM_3_2_X_Steel,unsigned ITEM_3_3_Y_Steel,
			 unsigned ITEM_6_1_HookSteel,unsigned ITEM_6_2_HookSteelSize,unsigned ITEM_6_3_HookSteelDistance,
			 unsigned ITEM_7_1_HookSteel,unsigned ITEM_7_2_HookSteelSize,unsigned ITEM_7_3_HookSteelDistance,unsigned ITEM_7_4_HookSteelDistance2,
			 unsigned ITEM_8_1_TieSteelSize,unsigned ITEM_8_2_X_TieSteel,unsigned ITEM_8_3_Y_TieSteel,
			 unsigned ITEM_9_1_CornerDoubleSteelSize,unsigned ITEM_9_2_X_CornerDoubleSteel,unsigned ITEM_9_3_Y_CornerDoubleSteel,
			 unsigned ITEM_10_1_CornerDoubleSteelSize,unsigned ITEM_10_2_X_CornerDoubleSteel, unsigned ITEM_10_3_Y_CornerDoubleSteel);
};
class COL_DXF : public DXF
{
public:
	string table_ID,layout_flag,title_each_side;
	vector<vector<column>> columns_dat;
	vector<string> columns;
	vector<string> stories;
public:

	virtual void fout_tables(ofstream& fout) const;
	virtual void fout_blocks(ofstream& fout) const;
	virtual void fout_entities(ofstream& fout) const;

	//vector<point> basepoints; 
public:
	//中階
	void draw_canvas(ofstream& fout, point left_down, point right_up)  const;
	void draw_table(ofstream& fout,point canvas_o, vector<string> columns,vector<string> stories)  const;
	void draw_columns(ofstream& fout,point canvas_left_up, vector<vector<column>> columns)  const;
	//輔助
	void draw_x_y_arrow(ofstream&,point left_down) const;
	void draw_column(ofstream&,point left_down,column column_dat) const;
	void draw_eyes(ofstream& fout, point loc,unsigned steel_size) const;
	void draw_hook(ofstream& fout, vector<point> points) const;
	void draw_tie(ofstream& fout, point p1, point p2,bool is_mirror = 0) const;

public:
	//資料
	void clear();
};
#endif