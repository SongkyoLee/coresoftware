#ifndef PHG4Cell_H__
#define PHG4Cell_H__

#include "PHG4CellDefs.h"
#include <g4main/PHG4Hit.h>
#include <phool/PHObject.h>

#include <cmath>
#include <climits>
#include <map>

class PHG4Cell: public PHObject
{
 public:
  typedef std::map<PHG4HitDefs::keytype, float> EdepMap;
  typedef EdepMap::iterator EdepIterator;
  typedef EdepMap::const_iterator EdepConstIterator;
  typedef std::pair<EdepIterator, EdepIterator> EdepRange;
  typedef std::pair<EdepConstIterator, EdepConstIterator> EdepConstRange;

  typedef std::map<int, float> ShowerEdepMap;
  typedef ShowerEdepMap::iterator ShowerEdepIterator;
  typedef ShowerEdepMap::const_iterator ShowerEdepConstIterator;
  typedef std::pair<ShowerEdepIterator, ShowerEdepIterator> ShowerEdepRange;
  typedef std::pair<ShowerEdepConstIterator, ShowerEdepConstIterator> ShowerEdepConstRange;

  typedef std::pair<unsigned short,std::map<int,int>> tpccompress;
  typedef std::map<unsigned short,tpccompress> tpctod;


  virtual ~PHG4Cell() {}

  virtual void identify(std::ostream& os = std::cout) const;
  virtual void Copy(PHG4Cell const &g4cell);
  friend std::ostream &operator<<(std::ostream & stream, const PHG4Cell * cell);
  virtual void Reset();

  // all methods connected to the cell id (encoding/decoding
  virtual void set_cellid(const PHG4CellDefs::keytype i) {return;}

  virtual PHG4CellDefs::keytype get_cellid() const {return ~0x0;}
  virtual bool has_binning(const PHG4CellDefs::CellBinning) const {return false;}

  // this adds hits to the g4 hit list map
  virtual void add_edep(const PHG4HitDefs::keytype g4hitid, const float edep) {return;}
  // this adds showers to the shower map
  virtual void add_shower_edep(const int g4showerid, const float edep) {return;}

  virtual EdepConstRange get_g4hits() {
    std::map <PHG4HitDefs::keytype, float> dummy;
    return std::make_pair(dummy.begin(), dummy.end());
  }

  virtual ShowerEdepConstRange get_g4showers() {
    std::map <int, float> dummy;
    return std::make_pair(dummy.begin(), dummy.end());
  }

  virtual short int get_detid() const {return -1;}
  // for backward compatibility, layers and detector ids are identical
  short int get_layer() const {return get_detid();}

  virtual void add_edep(const float f) {return;}
  virtual double get_edep() const {return NAN;}

  virtual void add_eion(const float f) {return;}
  virtual double get_eion() const {return NAN;}

  virtual void add_light_yield(const float lightYield){return;}
  virtual float get_light_yield() const {return NAN;}

  // get/set methodes - PLEASE add those ALPHABETICALLY

  virtual void set_chip_index(const int i) {return;}
  virtual int get_chip_index() const {return ~0x0;}

  virtual void set_half_stave_index(const int i) {return;}
  virtual int get_half_stave_index() const {return ~0x0;}

  virtual void set_ladder_phi_index(const int i) {return;}
  virtual int get_ladder_phi_index() const {return ~0x0;}

  virtual void set_ladder_z_index(const int i) {return;}
  virtual int get_ladder_z_index() const {return ~0x0;}

  virtual void set_module_index(const int i) {return;}
  virtual int get_module_index() const {return ~0x0;}

  virtual void set_phibin(const int i) {return;}
  virtual int get_phibin() const {return ~0x0;}

  virtual void set_pixel_index(const int i) {return;}
  virtual int get_pixel_index() const {return ~0x0;}

  virtual void set_stave_index(const int i) {return;}
  virtual int get_stave_index() const {return ~0x0;}

  virtual tpctod* get_train_of_digits() {return 0;}

  virtual void set_zbin(const int i) {return;}
  virtual int get_zbin() const {return ~0x0;}


  virtual void print() const {std::cout<<"PHG4Cellv1"<<std::endl;}

  //! Procedure to add a new PROPERTY tag:
  //! 1.add new tag below with unique value,
  //! 2.add a short name to PHG4Cell::get_property_info
  enum PROPERTY 
  {//
    // first various coordinates 1-20
    //! Maps coordinates
    prop_stave_index = 1,
    prop_half_stave_index = 2,
    prop_module_index = 3,
    prop_chip_index = 4,
    prop_pixel_index = 5,
    prop_phibin = 6,
    prop_zbin = 7,
    prop_ladder_z_index = 8,
    prop_ladder_phi_index = 9,
    //-- summed energy:  - 20-30  --
    //! deposited energy
    prop_edep = 21,
    //! ionizing energy loss
    prop_eion = 22,

    //! for scintillation detectors, the amount of light produced
    prop_light_yield = 23,

    //! max limit in order to fit into 8 bit unsigned number
    prop_MAX_NUMBER = UCHAR_MAX
  };

  enum PROPERTY_TYPE 
  {//
    type_int = 1,
    type_uint = 2,
    type_float = 3,
    type_unknown = -1
  };

  virtual bool  has_property(const PROPERTY prop_id) const {return false;}
  virtual float get_property_float(const PROPERTY prop_id) const {return NAN;}
  virtual int   get_property_int(const PROPERTY prop_id) const {return INT_MIN;}
  virtual unsigned int   get_property_uint(const PROPERTY prop_id) const {return UINT_MAX;}
  virtual void  set_property(const PROPERTY prop_id, const float value) {return;}
  virtual void  set_property(const PROPERTY prop_id, const int value) {return;}
  virtual void  set_property(const PROPERTY prop_id, const unsigned int value) {return;}
  static std::pair<const std::string,PROPERTY_TYPE> get_property_info(PROPERTY prop_id);
  static bool check_property(const PROPERTY prop_id, const PROPERTY_TYPE prop_type);
  static std::string get_property_type(const PROPERTY_TYPE prop_type);

 protected:
  PHG4Cell() {}
  virtual unsigned int get_property_nocheck(const PROPERTY prop_id) const {return UINT_MAX;}
  virtual void set_property_nocheck(const PROPERTY prop_id,const unsigned int) {return;}
  ClassDef(PHG4Cell,1)
};


#endif
