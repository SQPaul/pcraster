#ifndef INCLUDED_DAL_FILESYSTEMUTILS
#define INCLUDED_DAL_FILESYSTEMUTILS



// Library headers.

// PCRaster library headers.

// Module headers.
#ifndef INCLUDED_DAL_CONFIGURE
#include "dal_Configure.h"
#define INCLUDED_DAL_CONFIGURE
#endif

#ifndef INCLUDED_DAL_DATASPACE
#include "dal_DataSpace.h"
#define INCLUDED_DAL_DATASPACE
#endif

#ifndef INCLUDED_DAL_DEF
#include "dal_Def.h"
#define INCLUDED_DAL_DEF
#endif

#include <filesystem>



namespace boost {
  namespace gregorian {
    class date;
  }
}
namespace dal {
  class DataSpaceAddress;
}



namespace dal {

PCR_DAL_DECL bool  isReadable          (std::filesystem::path const& path);

PCR_DAL_DECL bool  isWritable          (std::filesystem::path const& path);

void               testPathnameIsEmpty (std::string const& pathName);

// PCR_DAL_DECL bool pathnameIsNative    (std::string const& pathname);

// PCR_DAL_DECL void testPathnameIsNative(std::string const& pathname);

void               testPathExists      (std::filesystem::path const& path);

void               testPathIsFileOrLinkToFile(
                                        std::filesystem::path const& path);

void               testPathIsReadable  (std::filesystem::path const& path);

PCR_DAL_DECL void  testPathIsWritable  (std::filesystem::path const& path);

PCR_DAL_DECL void  testFileCanBeOpenedForReading(
                                        std::filesystem::path const& path);

PCR_DAL_DECL std::filesystem::path timeStepPath83(
                                        std::string const& parent,
                                        std::string filename,
                                        size_t timeStep);

PCR_DAL_DECL std::filesystem::path timeStepPath83(
                                        std::filesystem::path const& path,
                                        size_t timeStep);

PCR_DAL_DECL std::filesystem::path timeStepPathNewStyle(
                                        std::string const& parent,
                                        std::string filename,
                                        size_t timeStep);

PCR_DAL_DECL std::filesystem::path timeStepPath(
                                        std::string const& parent,
                                        std::string const& filename,
                                        size_t timeStep,
                                        FilenameConvention convention=DALConvention);

PCR_DAL_DECL std::filesystem::path timeStepPath   (std::filesystem::path const& path,
                                        size_t timeStep,
                                        FilenameConvention convention=DALConvention);

PCR_DAL_DECL std::filesystem::path timeStepPath   (std::filesystem::path const& path,
                                        boost::gregorian::date const& date,
                                        FilenameConvention convention=DALConvention);

bool               canBeOpenedForReading(std::filesystem::path const& path);

PCR_DAL_DECL bool  exists              (std::filesystem::path const& path);

PCR_DAL_DECL bool  pathExists          (std::string const& name,
                                        DataSpace const& space,
                                        DataSpaceAddress const& address,
                                        FilenameConvention convention=DALConvention);

bool               remove              (std::filesystem::path const& path);

PCR_DAL_DECL std::filesystem::path addExtensionIfNeeded(
                                       std::string const& name,
                                       std::string const& extension);

std::filesystem::path addExtensionIfNeeded(
                                       std::filesystem::path const& path,
                                       std::string const& extension);

PCR_DAL_DECL boost::tuple<std::string, dal::DataSpace>
                   oldStackName2NameSpaceTuple(
                                        std::string const& name);

PCR_DAL_DECL std::filesystem::path pathForDataSpaceAddress(
                                        std::string const& name,
                                        DataSpace const& space,
                                        DataSpaceAddress const& address,
                                        FilenameConvention convention=DALConvention);

// With scenario.
//   With quantile.
//     With sample.
//       With time.
std::filesystem::path pathForScenarioQuantileSampleTime(
                                        std::string const& name,
                                        std::string const& scenarioName,
                                        float quantile,
                                        size_t sampleNumber,
                                        size_t timeStep,
                                        FilenameConvention convention=DALConvention);

//       Without time.
std::filesystem::path pathForScenarioQuantileSample(
                                        std::string const& name,
                                        std::string const& scenarioName,
                                        float quantile,
                                        size_t sampleNumber,
                                        FilenameConvention convention=DALConvention);
//     Without sample.
//       With time.
std::filesystem::path pathForScenarioQuantileTime(
                                        std::string const& name,
                                        std::string const& scenarioName,
                                        float quantile,
                                        size_t timeStep,
                                        FilenameConvention convention=DALConvention);

//       Without time.
std::filesystem::path pathForScenarioQuantile(
                                        std::string const& name,
                                        std::string const& scenarioName,
                                        float quantile,
                                        FilenameConvention convention=DALConvention);

//   Without quantile.
//     With sample.
//       With time.
std::filesystem::path pathForScenarioSampleTime(
                                        std::string const& name,
                                        std::string const& scenarioName,
                                        size_t sampleNumber,
                                        size_t timeStep,
                                        FilenameConvention convention=DALConvention);

//       Without time.
std::filesystem::path pathForScenarioSample(
                                        std::string const& name,
                                        std::string const& scenarioName,
                                        size_t sampleNumber,
                                        FilenameConvention convention=DALConvention);

//     Without sample.
//       With time.
std::filesystem::path pathForScenarioTime(
                                        std::string const& name,
                                        std::string const& scenarioName,
                                        size_t timeStep,
                                        FilenameConvention convention=DALConvention);

//       Without time.
std::filesystem::path pathForScenario(std::string const& name,
                                        std::string const& scenarioName,
                                        FilenameConvention convention=DALConvention);

// Without scenario.
//   With quantile.
//     With sample.
//       With time.
std::filesystem::path pathForQuantileSampleTime(
                                         std::string const& name,
                                         float quantile,
                                         size_t sampleNumber,
                                         size_t timeStep,
                                         FilenameConvention convention=DALConvention);

//       Without time.
std::filesystem::path pathForQuantileSample(
                                        std::string const& name,
                                        float quantile,
                                        size_t sampleNumber,
                                        FilenameConvention convention=DALConvention);

//     Without sample.
//       With time.
std::filesystem::path pathForQuantileTime(
                                        std::string const& name,
                                        float quantile,
                                        size_t timeStep,
                                        FilenameConvention convention=DALConvention);

//       Without time.
std::filesystem::path pathForQuantile(std::string const& name,
                                        float quantile,
                                        FilenameConvention convention=DALConvention);

//   Without quantile.
//     With sample.
//       With time.
std::filesystem::path pathForSampleTime(
                                        std::string const& name,
                                        size_t sampleNumber,
                                        size_t timeStep,
                                        FilenameConvention convention=DALConvention);

//       Without time.
std::filesystem::path pathForSample  (std::string const& name,
                                        size_t sampleNumber,
                                        FilenameConvention convention=DALConvention);

//     Without sample.
//       With time.
std::filesystem::path pathForTime    (std::string const& name,
                                        size_t timeStep,
                                        FilenameConvention convention=DALConvention);

//       Without time.
PCR_DAL_DECL std::filesystem::path pathFor(std::string const& name);

// std::string fixPathname                (std::string const& name);

//! Determines the file naming convention and extension used to name the data set.
/*!
  \param     .
  \return    Tuple of the file name convention and the extension.
  \exception .
  \warning   .
  \sa        .
  \todo      Make convention an argument. PCRConvention only needs to be used
             in case of CSFRasterDriver. Saves a lot of checking.

  This information can be determined once and used multiple times for the
  same \a name. This speeds up the search for individual files that comprise
  the data set.
*/
template<class CallBack>
inline boost::tuple<bool, FilenameConvention, std::string>
                   determineFilenameCharacteristics(
                                  CallBack const& callBack,
                                  std::string const& name,
                                  DataSpace const& space,
                                  DataSpaceAddress const& address,
                                  std::vector<std::string> const& extensions)
{
  // Check which of the filenaming conventions gets a hit.

  // Check convention without extension.
  if(callBack(pathForDataSpaceAddress(
         name, space, address, DALConvention).string())) {
    return boost::make_tuple(true, DALConvention, std::string());
  }

  // Check convention with extension.
  for(size_t i = 0; i < extensions.size(); ++i) {
    if(callBack(pathForDataSpaceAddress(name + extensions[i], space,
         address, DALConvention).string())) {
      return boost::make_tuple(true, DALConvention, extensions[i]);
    }
  }

  // Alternative filename conventions are only relevant in case the dataspace
  // is not empty.
  if(!space.isEmpty()) {
    // Check convention without extension.
    if(space.hasTime() &&
      std::filesystem::path(name).extension().string().size() < 4) {
      if(callBack(pathForDataSpaceAddress(name, space, address,
         PCRConvention).string())) {
        return boost::make_tuple(true, PCRConvention, std::string());
      }
    }

    // Check convention with extension.
    for(size_t i = 0; i < extensions.size(); ++i) {
      if(space.hasTime() && extensions[i].size() < 4) {
        if(callBack(pathForDataSpaceAddress(name + extensions[i], space,
             address, PCRConvention).string())) {
          return boost::make_tuple(true, PCRConvention, extensions[i]);
        }
      }
    }
  }

  return boost::make_tuple(false, UnknownFilenameConvention, std::string());
}

void               possibleFileBasedAttributeFileNames(
                                        std::filesystem::path const& path,
                                        std::vector<std::string>& leaves);

} // namespace dal

#endif
