#ifndef INCLUDED_DIS
#include "dis.h"
#define INCLUDED_DIS
#endif


// Library headers.
#ifndef INCLUDED_VECTOR
#include <vector>
#define INCLUDED_VECTOR
#endif

#ifndef INCLUDED_IOSTREAM
#include <iostream>
#define INCLUDED_IOSTREAM
#endif

#ifndef INCLUDED_SSTREAM
#include <sstream>
#define INCLUDED_SSTREAM
#endif


// PCRaster library headers.

// Module headers.
#ifndef INCLUDED_GRIDCHECK
#include "gridcheck.h"
#define INCLUDED_GRIDCHECK
#endif

#ifndef INCLUDED_COMMON
#include "common.h"
#define INCLUDED_COMMON
#endif

#ifndef INCLUDED_PCRMODFLOW
#include "pcrmodflow.h"
#define INCLUDED_PCRMODFLOW
#endif


#include <fstream>



/**
 * Destructor
 */
DIS::~DIS(){
}

/**
 * Constructor
 */
DIS::DIS(PCRModflow *mf) :
  d_mf(mf),
  d_itmuni(0),
  d_lenuni(0),
  d_perlen(1.0),
  d_nstp(1),
  d_tsmult(1.0),
  d_sstr("SS"),
  d_row_width(),
  d_col_width(),
  d_external_unit(300)
  {
}


/**
 * setting DIS package parameter
 */
void DIS::setParams(size_t itmuni, size_t lenuni, float perlen, size_t nstp, float tsmult, bool sstr){
  if(itmuni>5){
    std::stringstream stmp;
    stmp << "Time unit mismatch: Set value within interval [0,5]";
    d_mf->d_cmethods->error(stmp.str(), "setDISParameter");
  }
  if(lenuni>3){
    std::stringstream stmp;
    stmp << "Length unit mismatch: Set value within interval [0,3]";
    d_mf->d_cmethods->error(stmp.str(), "setDISParameter");
  }
  if(nstp<1){
    std::stringstream stmp;
    stmp << "Number of time steps mismatch: Number must be larger than 1";
    d_mf->d_cmethods->error(stmp.str(), "setDISParameter");
  }
  d_itmuni = itmuni;
  d_lenuni = lenuni;
  d_perlen = perlen;
  d_nstp = nstp;
  d_tsmult = tsmult;
  if(!sstr)
    d_sstr = "TR";
}



/**
 * write DIS to file
 */
// // // // // bool DIS::writeDIS() const{
// // // // //   std::ostringstream content;
// // // // //   content << "# Generated by PCRaster Modflow" << std::endl;
// // // // //   //
// // // // //   // Item 1: NLAY NROW NCOL NPER ITMUNI LENUNI
// // // // //   //
// // // // //   //  content << d_mf->d_nrMFLayer << " " << d_mf->d_nrOfRows << " " << d_mf->d_nrOfColumns;
// // // // //   //  content << " " << 1 << " " << d_itmuni << " " << d_lenuni << std::endl;
// // // // //   content << d_mf->dd_nrModflowLayer << " " << d_mf->d_nrOfRows << " " << d_mf->d_nrOfColumns;
// // // // //   content << " " << 1 << " " << d_itmuni << " " << d_lenuni << std::endl;
// // // // //   //
// // // // //   // Item 2:  LAYCBD
// // // // //   //
// // // // //   std::vector<bool>::reverse_iterator ri = d_mf->dd_isConfined.rbegin();
// // // // //   while(ri != (d_mf->dd_isConfined.rend())) {
// // // // //     if((!(ri + 1 == d_mf->dd_isConfined.rend()))&&(d_mf->dd_isConfined.at(*(ri + 1)) == true)){
// // // // //       content << " 1";
// // // // //       ++ri;
// // // // //     }
// // // // //     else{
// // // // //       content << " 0";
// // // // //     }
// // // // //     ++ri;
// // // // //   }
// // // // //   content << std::endl;
// // // // //   //
// // // // //   // Item 3:  DELR
// // // // //   //
// // // // //   write_col_width(content);
// // // // //   //
// // // // //   // Item 4:  DELC
// // // // //   //
// // // // //   write_row_width(content);
// // // // //   //
// // // // //   // Item 5:  Layer
// // // // //   //
// // // // //   int nrLayer = 1;
// // // // //   for(int i = d_mf->dd_nrLayer - 1; i >= 0; i--){
// // // // //     if(i == static_cast<int>(d_mf->dd_nrLayer - 1)){
// // // // //       content << "INTERNAL   1.0 (FREE)    -1    Top of system" << std::endl;
// // // // //     }
// // // // //     else if((i > 0) && (d_mf->dd_isConfined.at(i - 1) == 0)){
// // // // //       content << "INTERNAL    1.0 (FREE)   -1    Bottom layer " << nrLayer << std::endl;
// // // // //       nrLayer++;
// // // // //     }
// // // // //     else if((i > 0) && (d_mf->dd_isConfined.at(i - 1) == 1)){
// // // // //       content << "INTERNAL    1.0 (FREE)   -1    Bottom confinig bed layer " << nrLayer - 1 << std::endl;
// // // // //     }
// // // // //     else{
// // // // //       content << "INTERNAL    1.0 (FREE)   -1    Bottom confinig bed layer " << nrLayer - 1<< std::endl;
// // // // //     }
// // // // //     size_t pos = 0;
// // // // //     for(size_t j = 0; j < d_mf->d_nrOfRows; j++){
// // // // //       for(size_t k = 0; k < d_mf->d_nrOfColumns; k++){
// // // // //         double val = d_mf->d_baseArea->cell(pos).baseElevation();
// // // // //         for (int l = 0; l <= i; l++){
// // // // //           val += d_mf->d_baseArea->cell(pos)[l];
// // // // //         }
// // // // //         content << " " << val ;
// // // // //         pos++;
// // // // //       }
// // // // //       content << std::endl;
// // // // //     }
// // // // //   }
// // // // //
// // // // //   content <<  "INTERNAL   1.00 (FREE)   -1    Bottom of system" << std::endl;
// // // // //
// // // // //   size_t pos = 0;
// // // // //   for(size_t j = 0; j < d_mf->d_nrOfRows; j++){
// // // // //     for(size_t k = 0; k < d_mf->d_nrOfColumns; k++){
// // // // //       content << " " <<  d_mf->d_baseArea->cell(pos).baseElevation();
// // // // //       pos++;
// // // // //     }
// // // // //     content << std::endl;
// // // // //   }
// // // // //
// // // // //   // Item 7:  PERLEN NSTP TSMULT SS/TR
// // // // //   content << d_perlen  << " " << d_nstp << " " << d_tsmult << " " << d_sstr << std::endl;
// // // // //
// // // // //   return d_mf->d_cmethods->writeToFile("pcrmf.dis",content.str());
// // // // //
// // // // // }

/**
 * returns number of timesteps
 */
size_t DIS::getTimeSteps() const{
  return d_nstp;
}


/**
 * specification of the grid by PCR block
 */
void DIS::setLayer(const discr::Block &elevation, const discr::BlockData<INT4> &conf){
  d_mf->d_nrOfLayer = conf.cell(0).size() - 1;
  d_mf->d_nrBlockLayer = conf.cell(0).size();

  d_mf->dd_nrLayer = conf.cell(0).size();

  for(size_t curLayer = 0; curLayer < d_mf->d_nrBlockLayer; curLayer++){
    for(size_t curCell = 0; curCell < d_mf->d_nrOfCells; curCell++){
      d_mf->d_baseArea->addVoxel(curCell,elevation.cell(curCell)[curLayer]);
    }
  }

  for(size_t i = 0; i < d_mf->d_nrBlockLayer; i++){
    d_mf->d_quasiConfined.push_back(conf.cell(0)[i]);

    d_mf->dd_isConfined.push_back(conf.cell(0)[i]);
  }
  // to "correct" the top of layer 1
  d_mf->d_quasiConfined.push_back(0);


  for(size_t i = 1; i < d_mf->d_quasiConfined.size(); i++){
    if(! ((d_mf->d_quasiConfined.at(i)==0) && (d_mf->d_quasiConfined.at(i-1)==1))){
      d_mf->d_layer2BlockLayer.push_back(i-1);//
      d_mf->d_nrMFLayer++;
      d_mf->dd_nrModflowLayer++;
    }
  }
}

/**
 * adding layer on top of the grid
 */
bool DIS::addLayer(const float *values){
  return addLayer(values, 0);
}

/**
 * adding confined layer on top of the grid
 */
bool DIS::addConfinedLayer(const float *values){
  return addLayer(values, 1);
}

/**
 * setting the bottom layer
 */
bool DIS::createBottom(const float *lower, const float *upper){
  // reset grid if one of the
  if(d_mf->d_gridIsFixed == true) {
    d_mf->resetGrid(false);
    d_mf->d_gridIsFixed = false;
  }
  // name for errormessages
  d_mf->d_methodName = "createBottomLayer map 1";
  // test input on missing values
  d_mf->d_gridCheck->testMV(lower, d_mf->d_methodName);

  d_mf->d_methodName = "createBottomLayer map 2";
  d_mf->d_gridCheck->testMV(upper, d_mf->d_methodName);

  // setting the base elevation
  for(size_t i = 0; i < d_mf->d_nrOfCells; i++){
    d_mf->d_baseArea->cell(i) = lower[i];
  }

  // adding the layer elevation
  for(size_t i = 0; i < d_mf->d_nrOfCells; i++){
    d_mf->d_baseArea->addVoxel(i, upper[i] - d_mf->d_baseArea->cell(i).baseElevation());
  }
  // base layer must not be no confining bed
  d_mf->d_quasiConfined.push_back(0); //
  d_mf->d_quasiConfined.push_back(0);

  //
  d_mf->d_nrOfLayer++;
  d_mf->d_nrBlockLayer++;
  d_mf->d_nrMFLayer++;
  d_mf->d_layer2BlockLayer.push_back(0);

  d_mf->dd_nrModflowLayer++;
  d_mf->dd_nrLayer++;
  // bottom layer must not be no confining bed
  d_mf->dd_isConfined.push_back(false);


  assert(!d_mf->d_baseArea->cell(0).empty());
  assert(!d_mf->d_layer->cell(0).empty());
  assert(d_mf->d_baseArea->cell(0).size() == d_mf->d_layer->cell(0).size());
  d_mf->setBlockData(*(d_mf->d_layer), upper, 0);
  // check if bottom layer  elevation > 0.0
  d_mf->d_gridCheck->testElevation();
  return true;
}



/**
 * adding a layer on top of the grid
 * @param values elevation values
 * @param confined true - confined
 * @return
 */
bool DIS::addLayer(const float *values, bool confined){

  if(d_mf->d_gridIsFixed == true) {
    d_mf->resetGrid(false);
    d_mf->d_gridIsFixed = false;
  }

  d_mf->d_gridCheck->testElevation();

  d_mf->d_methodName = "addLayer";
  if(confined == true)
    d_mf->d_methodName = "addConfinedLayer";

  d_mf->d_gridCheck->testMV(values, d_mf->d_methodName);

  // two confined layer not allowed
  if(confined == true){
    if(d_mf->d_lastIsConfined == true){
      std::string stmp("Grid specification: two consecutive confining beds are not allowed");
      d_mf->d_cmethods->error(stmp, d_mf->d_methodName);
    }
    d_mf->d_lastIsConfined = true;
  }
  else {
    d_mf->d_lastIsConfined = false;
  }

  // add thickness of new-previous layer to grid
  for(size_t i = 0; i < d_mf->d_nrOfCells; i++) {
    d_mf->d_baseArea->addVoxel(i, values[i] - d_mf->d_layer->cell(i)[d_mf->d_nrOfLayer]);
  }
  // adapt confined layer information
  if(confined){
    // bottom of confined must be adapted
    /// \todo this should be changed...
    size_t size = d_mf->d_quasiConfined.size() - 1;
    d_mf->d_quasiConfined.at(size) = confined;
    // top of confined

  }
  // top of layer
  d_mf->d_quasiConfined.push_back(false);

  d_mf->d_nrOfLayer++;
  d_mf->d_nrBlockLayer++;

  if(!confined){
    d_mf->dd_isConfined.push_back(false);
    d_mf->dd_nrModflowLayer++;
  }
  else{
    d_mf->dd_isConfined.push_back(true);
  }
  d_mf->dd_nrLayer++;


  // store new layer
  d_mf->setBlockData(*(d_mf->d_layer), values, d_mf->d_nrOfLayer);

  if(! ((d_mf->d_quasiConfined.at(d_mf->d_nrBlockLayer)==0) && (d_mf->d_quasiConfined.at(d_mf->d_nrBlockLayer-1)==1))) {
    d_mf->d_layer2BlockLayer.push_back(d_mf->d_nrBlockLayer-1);//
    d_mf->d_nrMFLayer++;
  }
  return true;
}



void DIS::createBottom(const calc::Field *lower, const calc::Field *upper){
  // reset grid if one of the
  if(d_mf->d_gridIsFixed == true) {
    d_mf->resetGrid(false);
    d_mf->d_gridIsFixed = false;
  }
  // name for errormessages
  d_mf->d_methodName = "createBottomLayer map 1";
  // test input on missing values
  d_mf->d_gridCheck->testMV(lower->src_f(), d_mf->d_methodName);
  d_mf->d_methodName = "createBottomLayer map 2";
  d_mf->d_gridCheck->testMV(upper->src_f(), d_mf->d_methodName);
  // setting the base elevation
  REAL8 value = 0.0;
  for(size_t i = 0; i < d_mf->d_nrOfCells; i++){
    lower->getCell(value, i);
    d_mf->d_baseArea->cell(i) = value;
  }

  // adding the layer elevation
  value = 0.0;
  for(size_t i = 0; i < d_mf->d_nrOfCells; i++){
    upper->getCell(value, i);
    d_mf->d_baseArea->addVoxel(i, value - d_mf->d_baseArea->cell(i).baseElevation());
  }
  // base layer must not be no confining bed
  d_mf->d_quasiConfined.push_back(0); //
  d_mf->d_quasiConfined.push_back(0);

  //
  d_mf->d_nrOfLayer++;
  d_mf->d_nrBlockLayer++;
  d_mf->d_nrMFLayer++;
  d_mf->d_layer2BlockLayer.push_back(0);

  d_mf->dd_nrModflowLayer++;
  d_mf->dd_nrLayer++;
  // bottom layer must not be no confining bed
  d_mf->dd_isConfined.push_back(false);



  d_mf->setBlockData(*(d_mf->d_layer), upper->src_f(), 0);
  // check if bottom layer  elevation > 0.0
  d_mf->d_gridCheck->testElevation();
}


void DIS::addLayer(const calc::Field *values){
  addLayer(values->src_f(), 0);
}


void DIS::addConfinedLayer(const calc::Field *values){
  addLayer(values->src_f(), 1);
}


void DIS::reset_row_width(){
  d_row_width.clear();
}


void DIS::append_row_width(float width){
  d_row_width.push_back(width);
}


void DIS::write_row_width(std::ostringstream& content) const {

  if(d_row_width.size() == 0){
    content << "CONSTANT " << d_mf->d_cellsize << std::endl;
  }
  else{
    content << "INTERNAL   1.0 (FREE)    -1    DELC" << std::endl;
    for(size_t i = 0; i < d_row_width.size(); i++){
      content << d_row_width[i] << " ";
    }
    content << std::endl;
  }

}


void DIS::reset_col_width(){
  d_col_width.clear();
}


void DIS::append_col_width(float width){
  d_col_width.push_back(width);
}


void DIS::write_col_width(std::ostringstream& content) const {

  if(d_col_width.size() == 0){
    content << "CONSTANT " << d_mf->d_cellsize << std::endl;
  }
  else{
    content << "INTERNAL   1.0 (FREE)    -1    DELR" << std::endl;
    for(size_t i = 0; i < d_col_width.size(); i++){
      content << d_col_width[i] << " ";
    }
    content << std::endl;
  }

}







void DIS::write_dis(std::string const& path) const {
  //

  std::ostringstream content;
  content << "# Generated by PCRaster Modflow" << std::endl;
  //
  // Item 1: NLAY NROW NCOL NPER ITMUNI LENUNI
  //
  content << d_mf->dd_nrModflowLayer << " " << d_mf->d_nrOfRows << " " << d_mf->d_nrOfColumns;
  content << " " << 1 << " " << d_itmuni << " " << d_lenuni << std::endl;
  //
  // Item 2:  LAYCBD
  //
  std::vector<bool>::reverse_iterator ri = d_mf->dd_isConfined.rbegin();
  while(ri != (d_mf->dd_isConfined.rend())) {
    if((!(ri + 1 == d_mf->dd_isConfined.rend()))&&(d_mf->dd_isConfined.at(*(ri + 1)) == true)){
      content << " 1";
      ++ri;
    }
    else{
      content << " 0";
    }
    ++ri;
  }
  content << std::endl;
  //
  // Item 3:  DELR
  //
  write_col_width(content);
  //
  // Item 4:  DELC
  //
  write_row_width(content);
  //
  // Item 5:  Layer
  //
  int nrLayer = 1;
  for(int i = d_mf->dd_nrLayer - 1; i >= 0; i--){
    if(i == static_cast<int>(d_mf->dd_nrLayer - 1)){
      content << "EXTERNAL " << d_external_unit << " 1.0 (FREE) -1  Top of system" << std::endl;
    }
    else if((i > 0) && (d_mf->dd_isConfined.at(i - 1) == 0)){
      content << "EXTERNAL " << d_external_unit << " 1.0 (FREE) -1  Bottom layer " << nrLayer << std::endl;
      nrLayer++;
    }
    else if((i > 0) && (d_mf->dd_isConfined.at(i - 1) == 1)){
      content << "EXTERNAL " << d_external_unit << " 1.0 (FREE) -1  Bottom confinig bed layer " << nrLayer - 1 << std::endl;
    }
    else{
      content << "EXTERNAL " << d_external_unit << " 1.0 (FREE) -1  Bottom confinig bed layer " << nrLayer - 1<< std::endl;
    }
  }

  content <<  "EXTERNAL 300 1.0 (FREE) -1  Bottom of system" << std::endl;

  // Item 7:  PERLEN NSTP TSMULT SS/TR
  content << d_perlen  << " " << d_nstp << " " << d_tsmult << " " << d_sstr << std::endl;

  d_mf->d_cmethods->writeToFile("pcrmf.dis",content.str());
}




void DIS::write_dis_array(std::string const& path) const {

  std::ofstream content("pcrmf_elev.asc");

  if(!content.is_open()){
    std::cerr << "Can not write " << "pcrmf_elev.asc" << std::endl;

    exit(1);
  }

  int nrLayer = 1;
  for(int i = d_mf->dd_nrLayer - 1; i >= 0; i--){
    size_t pos = 0;
    for(size_t j = 0; j < d_mf->d_nrOfRows; j++){
      for(size_t k = 0; k < d_mf->d_nrOfColumns; k++){
        double val = d_mf->d_baseArea->cell(pos).baseElevation();
        for (int l = 0; l <= i; l++){
          val += d_mf->d_baseArea->cell(pos)[l];
        }
        content << " " << val;
        pos++;
      }
      content << "\n";
    }
  }

  // Bottom of system

  size_t pos = 0;
  for(size_t j = 0; j < d_mf->d_nrOfRows; j++){
    for(size_t k = 0; k < d_mf->d_nrOfColumns; k++){
      content << " " <<  d_mf->d_baseArea->cell(pos).baseElevation();
      pos++;
    }
    content << "\n";
  }

  content.close();
}


void DIS::update_parameter(float stressPeriodLength, size_t nrOfTimesteps, float timeStepMultiplier){
  d_perlen = stressPeriodLength;
  d_nstp = nrOfTimesteps;
  d_tsmult = timeStepMultiplier;
}

