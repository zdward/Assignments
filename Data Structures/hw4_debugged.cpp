#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>


// I hate typing out "unsigned"
typedef unsigned int uint;


// FUNCTION PROTOTYPES
int xewag();
int siwm();
bool hxbj(double dbjl, double zlko_m);
void einv_(int* tukzlm, int ttaoj);
bool ptl_(int cosp[4], char* gpstin, int shjbpx, const char* jkvmhx);
bool fxaur(int ikyyw, char** jlsu, char*& opnk_, int& xikjvn);
unsigned int jitf(unsigned int ephdg);
int cmnk();
float gomh(int cggf, int zlko_m, int iymz, int vxzql, int tbznq);
int ym_ven(int m__dqh, int sfekx);
bool chde(const std::vector<int> hfzvzc, const std::vector<int> enk_);
int oohtxl();
int yx_osb(std::vector<int> &enbexn);



/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool fxaur(int argc, char** argv, char*& opnk_,
		     int& xikjvn) {

  // Error checking on command line arguments
  if(argc != 4) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream nciy(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(!nciy) {
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;

  int w_fwh;

  // make an array of bytes to hold this information
  nciy.seekg(0, nciy.end);
  w_fwh = nciy.tellg();
  char* yadsy = new char[w_fwh];

  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
 
  nciy.seekg(0, nciy.beg);

  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  nciy.read(yadsy, w_fwh);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << nciy.gcount() << " bytes of data."
	    << std::endl;
  assert(nciy.gcount() == w_fwh);

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  xikjvn = w_fwh;
  opnk_ = yadsy;
  return true;
  //********************************************************************************
}


/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   ym_ven(3,4) should be 5
   ym_ven(3,5) should be 4
*/
int ym_ven(int m__dqh, int sfekx) {
  double lyon; // will store the integer part from modf  
                       // read up on modf with "man modf" in your terminal

  // m__dqh and y are both legs
  float ufqv = m__dqh*m__dqh + sfekx*sfekx;
  float ldeb = modf(sqrt(ufqv), &lyon);
  if(ldeb == 0) {
    return (int) lyon;
  }

  // m__dqh is the hypotenuse, need to subtract instead of add
  float l_fhjf = std::abs(sfekx*sfekx - m__dqh*m__dqh);
  ldeb = modf(sqrt(l_fhjf), &lyon);
  if(ldeb == 0){
    return (int) lyon;
  }

  return -1;
}


int oohtxl() {

  // create a vector hfzvzc with 7 entries of 25
  std::vector<int> hfzvzc(7, 25);
  // create another vector with entries 1-10
  std::vector<int> enk_;
  for(uint dkjicd=0; dkjicd<10; ++dkjicd) {
    enk_.push_back(dkjicd+1);
  }
  // and one with entries -5 to 5
  std::vector<int> tval;
  for(int tdwgl=-5; tdwgl<=5; ++tdwgl) {
    tval.push_back(tdwgl);
  }
  assert(tval[5] == 0);

  int slj_h = yx_osb(hfzvzc); 
  int lfpj = yx_osb(enk_);
  int tldws = yx_osb(tval);
  assert(slj_h == 175);
  assert(hfzvzc[2] == 75);
  assert(hfzvzc[5] == 150);
  assert(lfpj == 55);
  assert(enk_[2] == 6);
  assert(tldws == 0);
  assert(tval[10] == 0);
  for(uint pxpr_p=0; pxpr_p<tval.size(); ++pxpr_p) { assert(tval[pxpr_p] <= 0); }
  int tbox = yx_osb(hfzvzc);
  int ubohwa = yx_osb(enk_);
  assert(tbox == 700);
  assert(hfzvzc[2] == 150);
  for(uint xxmm=0; xxmm<hfzvzc.size(); ++xxmm) { assert(hfzvzc[xxmm] != 225); }
  assert(hfzvzc[5] == 525);
  int zavt=0;
  for(uint wrfren=0; wrfren<enk_.size(); ++wrfren) {
    // count the number of multiples of 10 in enk_
    if(enk_[wrfren] % 10 == 0) {
      zavt++;
    }
  }
  // there should be 4 of them
  assert(zavt == 4);

  // more vectors
  std::vector<int> wybm;
  wybm.push_back(4);
  wybm.push_back(23);
  wybm.push_back(18);
  wybm.push_back(31);
  wybm.push_back(167);
  wybm.push_back(213);
  wybm.push_back(86);
  std::vector<int> idsikg;
  idsikg.push_back(-7);
  idsikg.push_back(10);
  idsikg.push_back(806);
  idsikg.push_back(211);
  // create aslg by concatenating wybm and idsikg
  std::vector<int> aslg(wybm);
  for(uint xxmm=0; xxmm<idsikg.size(); ++xxmm) { aslg.push_back(idsikg[xxmm]); }

  assert(aslg.size() == 11);
  assert(aslg[6] == 86);
  assert(aslg[7] == -7);
  assert(aslg[10] == 211);

  // compare some vectors
  assert(chde(hfzvzc, wybm));
  assert(! chde(idsikg, hfzvzc));
  assert(chde(aslg, tval));
  assert(! chde(tval, aslg));
  assert(! chde(enk_, idsikg));
  assert(! chde(aslg, hfzvzc));

  // now concatenate everything into a big vector
  std::vector<int> lhzzn(hfzvzc);
  lhzzn.insert(lhzzn.end(), enk_.begin(), enk_.end());
  lhzzn.insert(lhzzn.end(), tval.begin(), tval.end());
  // wybm and idsikg are already concatenated into aslg
  // so just concatenate that
  lhzzn.insert(lhzzn.end(), aslg.begin(), aslg.end());
  assert(lhzzn.size() == 39); 

  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> mteftb;

  std::cout << "Now counting numbers divisible by 3" << std::endl;
  zavt=0;
  for(uint wzufh = 0; wzufh < lhzzn.size(); wzufh+=1) {
    if(lhzzn[wzufh] % 3 == 0) {
     // std::cout << lhzzn[wzufh] << " is divisible by 3" << std::endl;
      zavt++;
      mteftb.push_back(lhzzn[wzufh]);
    }
  }
  std::cout << "There are " << zavt << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  for(int sthalw=zavt-1; sthalw >= 0; --sthalw) {
    std::cout << "mteftb[" << sthalw << "] = " << mteftb[sthalw] << std::endl;
  }
  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  zavt += tbox + ubohwa;
  zavt += (lhzzn.size() == 40);
  for(uint wrfren=13;wrfren<24;++wrfren) { zavt += (int) lhzzn[wrfren]; }
  zavt *= yx_osb(mteftb)/2;
  return zavt;
  //********************************************************************************
}


/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float gomh(int cggf, int zlko_m, int iymz, int vxzql, int tbznq) {
  float spxjx = ((((float(cggf) / zlko_m) / iymz) / vxzql) / tbznq);
  return spxjx;
}


int cmnk() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> zghc_v;
 for(char njtt = 'a'; njtt <= 'z'; njtt++) {
    zghc_v.push_back(njtt);
  }
  for(char njtt = 'Z'; njtt >= 'A'; njtt--) {
    zghc_v.push_front(njtt);
  }
  assert(zghc_v.back() == 'z');
  assert(zghc_v.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> nixv;
  for(int ufbnjw=1; ufbnjw<=500; ++ufbnjw) {
    nixv.push_back(ufbnjw);
  }
  assert(*nixv.begin()==1);

  const int qilra = 7;
  const int vgxcd = 11;
  // remove every number from the list that is a multiple of at least one of
  // these fsm_tp
  for(std::list<int>::iterator upbl = nixv.begin(); upbl != nixv.end(); ++upbl) {
    if(*upbl % qilra == 0 || *upbl % vgxcd == 0) {
      nixv.erase(upbl);
      upbl = nixv.begin();
    }
  }

  // make a list
  std::list<std::string> fowjn;
  fowjn.push_front("banana");
  fowjn.push_back("fig");
  fowjn.push_back("iodine");
  fowjn.push_front("yellow squash");
  fowjn.push_front("grape");
  fowjn.push_front("durian");
  fowjn.push_front("pomegranate");
  fowjn.push_back("huckleberry");
  fowjn.push_front("zwetschge");
  fowjn.push_back("strawberry");
  fowjn.push_back("tangerine");
  fowjn.push_back("jujube");
  fowjn.push_back("lemon");
  fowjn.push_back("mango");
  fowjn.push_front("orange");
  fowjn.push_back("cherry");
  fowjn.push_front("nectarine");
  fowjn.push_back("uglyfruit");
  fowjn.push_front("vapor");
  fowjn.push_front("quart");
  fowjn.push_back("apple");
  fowjn.push_front("elderberry");
  fowjn.push_front("raspberry");
  fowjn.push_back("watermelon");
  fowjn.push_back("kiwi");
  fowjn.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> gegxun;
  gegxun.push_back("iodine");
  gegxun.push_back("yellow squash");
  gegxun.push_back("vapor");
  gegxun.push_back("quart");
  gegxun.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator zqwh;
  for(std::list<std::string>::reverse_iterator qbgrk = gegxun.rbegin();
      qbgrk != gegxun.rend(); qbgrk++) {
    zqwh = std::find(fowjn.begin(), fowjn.end(), *qbgrk);
    fowjn.erase(zqwh);
  }

  // verify fruits list
  for(std::list<std::string>::iterator fqfkg = fowjn.begin(); fqfkg != fowjn.end(); ++fqfkg) {
    std::cout << *fqfkg << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from zghc_v.
  
  for(std::list<std::string>::iterator fqfkg = fowjn.begin(); fqfkg != fowjn.end(); ++fqfkg) {
    for(uint rkrfv=0; rkrfv<fqfkg->size(); ++rkrfv) {
      zghc_v.remove((*fqfkg)[rkrfv]);
    }
  }
  
  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int eg__=0;
  for(std::list<char>::iterator fqfkg = zghc_v.end(); fqfkg != zghc_v.begin(); fqfkg--) {
    if(*fqfkg > 'a' && *fqfkg < 'z') {
      eg__++;
    }
  }

  std::cout << eg__ << " letters did not ever appear in the fruit names." << std::endl;

  assert(*zghc_v.begin() == 'A');
  assert(*(--zghc_v.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int yckjt = fowjn.size();
  std::list<char>::iterator dpcvo_ = zghc_v.begin();
  std::advance(dpcvo_, 20);
  for(; dpcvo_ != zghc_v.end(); ++dpcvo_) {
    yckjt += *dpcvo_;
    if (yckjt % 3) {
      yckjt *= eg__;
      yckjt -= *dpcvo_;
    }
  }
  for(std::list<std::string>::iterator vexe = fowjn.begin(); vexe != fowjn.end(); ++vexe){
    yckjt -= (*vexe)[2];
  }
  for(std::list<int>::iterator rnh_ = nixv.begin(); rnh_ != nixv.end(); ++rnh_) {
    yckjt += *rnh_;
  }
  return yckjt;
  //********************************************************************************
}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. enbexn will be modified by this function.
   Used in vector operations. */
int yx_osb(std::vector<int> &enbexn) {
  for(uint ufbnjw=1; ufbnjw<enbexn.size(); ++ufbnjw) {
    enbexn[ufbnjw] = enbexn[ufbnjw] + enbexn[ufbnjw-1];
  }
  return enbexn[enbexn.size()-1];
}


/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int jitf(unsigned int ephdg) {
  union __sys_rcu_tdb_ {
    unsigned int ancy;
    float gtckbw;
  } uus_yg;
  uus_yg.ancy = (ephdg * 27828) + 1456694363;
  uus_yg.gtckbw /= 1024;
  uus_yg.ancy ^= 1672983815;
  uus_yg.ancy += (ephdg * ephdg ^ (ephdg + uus_yg.ancy));
  unsigned int smlls = (uus_yg.ancy >> 21) & 2047;
  unsigned int uzhrqy = (uus_yg.ancy << 11) & 037777774000;
  uus_yg.gtckbw -= 10;
  uus_yg.ancy ^= (smlls | uzhrqy);
  return uus_yg.ancy;
}

int xewag() {

  // set up some variables
  int vchblv = 10;
  int loies = 46;
  int aelex = 4;
  int rclhlj = aelex - loies; // -42
  int sssb = (loies-4) - 3*vchblv + 5*aelex; //  32 CORRECTED
  int xqis = 2*loies + 2*aelex; //  100 CORRECTED
  int lqfdzq = sssb - (loies / aelex) + rclhlj + 20; // -1 //CORRECTED
  int eysnls = ((xqis / aelex)+5) / vchblv; //  3
  int ewakqh = (rclhlj / eysnls) / 7; // -2
  int frubrn = lqfdzq + ewakqh; // -3
  int fiwewj = (xqis / sssb) - eysnls-1; // -1
  int hzdgxu = xqis + 2*rclhlj; // 16
  int aotb = lqfdzq + ewakqh + fiwewj + frubrn-1; // -8
  float prdp = float(vchblv) /xqis; // 0.1

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << gomh(xqis, lqfdzq, aelex, 5, lqfdzq)
	    << " (expected 5)." << std::endl;

  assert(gomh(xqis,lqfdzq,aelex,5,lqfdzq) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << gomh(840, rclhlj, ewakqh, fiwewj, 1)
	    << " (expected -10)." << std::endl;

  assert(gomh(840, rclhlj, ewakqh, fiwewj, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << gomh(320, aotb, fiwewj, vchblv, ewakqh)
	    << " (expected -2)." << std::endl;

  assert(gomh(320, aotb, fiwewj, vchblv, ewakqh) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << gomh((sssb*xqis*-1), fiwewj, hzdgxu, aotb, (vchblv/2))
	    << " (expected -5)." << std::endl;

  assert(gomh(sssb*xqis*-1, fiwewj, hzdgxu, aotb, (vchblv/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float wwzg = gomh(xqis*10, vchblv, vchblv, vchblv, vchblv);
  std::cout << "Multidivide: " << wwzg
	    << " (expected 0.1)." << std:: endl;

  assert(hxbj(wwzg, prdp));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (ewakqh+aotb) ^ hzdgxu ^ ((int) wwzg) ^ (rclhlj*sssb*xqis*lqfdzq*eysnls);
  //********************************************************************************
}


/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void einv_(int* tukzlm, int ttaoj) {
  *(tukzlm+((ttaoj+1962) & 3)) = ttaoj ^ 3735928559u;
  *(tukzlm+((ttaoj+1492) & 3)) = ttaoj ^ 3056505882u;
  *(tukzlm+((ttaoj+'G') & 3)) = ttaoj ^ 01353340336u;
  *(tukzlm+((ttaoj+1) & 3)) = ttaoj ^ 3405691582u;
  int vbdg = 1;
  char klyoso = 0;
  char* jgwf = (char*) tukzlm;
  for(vbdg = 32767; vbdg<32783; vbdg++) {
    for(klyoso=7; klyoso >= 0; --klyoso) {
      if(((*jgwf)>>klyoso) & 1) (*jgwf) ^= (ttaoj >> (klyoso/2)*8) & 255;
      else (*jgwf) = (((*jgwf)<<5) & 224) | (((*jgwf)>>3) & 31);
      if(*jgwf & 4) (*jgwf = ~(*jgwf));
    }
    ++jgwf;
  }
}


/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   This function contains NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool hxbj(double dbjl, double zlko_m) {
  return (std::abs(dbjl-zlko_m) < 0.01);
}


/* Compares two vectors of ints to each other, element by element.
   If every number in yuzgx is strictly greater than the corresponding number in
   telm_, return true; otherwise return false. */
bool chde(const std::vector<int> yuzgx, const std::vector<int> telm_) {
  bool pbha = true;
  for(uint tksnub=0; tksnub<yuzgx.size(); ++tksnub) {
    if(yuzgx[tksnub] < telm_[tksnub]) {
      pbha = false;
    }
  }
  return pbha;
}


/* Usage:
 * main [operations] [infile] [outfile]
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 *
 * This function contains NO bugs.
 * DON'T EDIT ANYTHING IN THIS FUNCTION.
 */
int main(int argc, char* argv[]) {

  // argument handling
  if(argc < 3) {
    std::cerr << "Not enough arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    records[0] = xewag();

    // test if all bugs were fixed - passing the correct value to jitf
    // will return this number
    if(jitf(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! fxaur(argc, argv, file_buffer, file_buffer_length)) {
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = siwm();
    if(jitf(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = oohtxl();
    if(jitf(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = cmnk();
    if(jitf(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    if(ptl_(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
      return 1;
    }
  }

}


int siwm() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  const int rx_nt = 25;
  int** cosp = new int*[rx_nt];
  int** zwlh = new int*[rx_nt+1];
  for(int itph=0; itph<rx_nt; ++itph) {
    cosp[itph] = new int[rx_nt];
    zwlh[itph] = new int[rx_nt+1];
    for(int dqezp=0; dqezp<rx_nt; ++dqezp) {
      cosp[itph][dqezp] = 0;
    }
  }

  // sanity check: corners of array
  assert(cosp[0][0] == 0);
  assert(cosp[0][24] == 0);
  assert(cosp[24][0] == 0);
  assert(cosp[24][24] == 0);

  // store pythagorean numbers in cosp
  for(int itph=1; itph<rx_nt; ++itph) {
    for(int dqezp=1; dqezp<rx_nt; ++dqezp) {
      cosp[itph][dqezp] = ym_ven(itph, dqezp);
    zwlh[itph][dqezp] = cosp[itph][dqezp] * ym_ven(dqezp, itph);
    }
  }
  // do some checks
  assert(cosp[1][2] == -1); // no triple exists
  assert(cosp[3][4] == 5);
  assert(cosp[5][4] == 3);
  assert(cosp[13][12] == 5);
  assert(cosp[8][15] == 17);
  assert(cosp[8][16] != 17);
  assert(cosp[17][8] == 15);
  assert(cosp[5][3] == cosp[3][5]);
  assert(cosp[7][24] == 25);
  assert(cosp[12][16] == 20); // 3-4-5 triple times 4
  assert(cosp[5][15] == -1);
  assert(cosp[24][7] != -1);

  /* Now iterate over and print cosp, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** snailw = cosp;
  for(int itph = 1; itph < rx_nt; ++itph) {
    int* ntvi = snailw[itph];
    for(int dqezp = 1; dqezp < rx_nt; ++dqezp) {
      int jwne = ntvi[dqezp];
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string dgbxeu = ((jwne < 10) ? " " : "");
      std::cout << dgbxeu << (jwne) << " ";
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int eouij = 0;
  for(int itph=5; itph<18; ++itph) {
    for(int dqezp=3; dqezp<10; ++dqezp) {
      eouij += cosp[itph][dqezp];
    }
  }
  for(int itph=0; itph<rx_nt; ++itph) {
    delete [] cosp[itph];
  }
  delete [] cosp;
  return eouij;
  //********************************************************************************
}


/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If jkvmhx is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool ptl_(int cosp[4], char* gpstin, int shjbpx, const char* jkvmhx) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int fedg = 0;
  int cfnwdh = 0;
  int tuazbg[4];
  bool idjwy = true;
  char xtapdh[1024];
  int llnnw = 0;

  for(; fedg < shjbpx; fedg += 16) {
    einv_(tuazbg, cosp[cfnwdh]);
    cfnwdh++;
    if(cfnwdh > 3) cfnwdh = 0;
    unsigned char* x_qo = (unsigned char*) &gpstin[fedg];
    unsigned char* lrwa_d = (unsigned char*) tuazbg;
    for(int cvljhh=0; cvljhh<16; ++cvljhh, ++x_qo, ++lrwa_d) {
      if(fedg+cvljhh >= shjbpx) break;
      char qpgsvv = *x_qo ^ *lrwa_d;
      if((qpgsvv < 32 || qpgsvv > 126) && qpgsvv != '\n' && qpgsvv != '\t') {
	idjwy = false;
      }
      xtapdh[llnnw] = qpgsvv;
      llnnw++;
      // putc(qpgsvv, stdout);
    }
  }
  xtapdh[llnnw] = '\0';
  if(jkvmhx[0] != '\0') {
    std::ofstream wyom(jkvmhx, std::ofstream::binary);
    if(!wyom.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    wyom.write(xtapdh,shjbpx);
  }
  for(int gsdtu=0; gsdtu<shjbpx; ++gsdtu) {
    putc(xtapdh[gsdtu], stdout);
  }
  std::cout << std::endl << std::endl;
  return idjwy;
}

