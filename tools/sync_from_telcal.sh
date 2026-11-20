#!/usr/bin/env bash
# Copy the ATM C++ sources/headers from a TELCAL checkout into pyATM/cpp/ATM.
#
# Usage: tools/sync_from_telcal.sh [TELCAL_ATM_DIR]
#   TELCAL_ATM_DIR defaults to ../TELCAL/TelCalResults/Libraries/ATM (relative to the pyATM root)
#
# Rules:
#   - only files tracked by git in TELCAL are copied
#   - the unused *_2024 variants, Makefiles and the ATMVersion template are not copied
#   - ATMVersion.cpp is regenerated from ATM_VERSION (same logic as the TelCal Makefile)
#   - cpp/ATM/TELCAL_SOURCE records the TELCAL commit the copy was taken from
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC="${1:-${ROOT}/../TELCAL/TelCalResults/Libraries/ATM}"
SRC="$(cd "${SRC}" && pwd)"
DST="${ROOT}/cpp/ATM"

[[ -f "${SRC}/src/ATM_VERSION" ]] || { echo "ERROR: ${SRC} is not an ATM directory" >&2; exit 1; }

rm -rf "${DST}/include" "${DST}/src"
mkdir -p "${DST}/include" "${DST}/src"

cd "${SRC}"
for f in $(git ls-files include src); do
  case "$(basename "$f")" in
    *_2024.*|Makefile*|.template|ATM_TAG|ATMVersion.cpp) continue ;;
  esac
  cp -p "$f" "${DST}/$f"
done
mv "${DST}/src/ATM_VERSION" "${DST}/ATM_VERSION"

# Regenerate ATMVersion.cpp exactly as TelCal's src/Makefile (do_release target) does
ATM_VER="$(sed 's/ALMA.*//; s/ //g' "${DST}/ATM_VERSION")"
ATM_TAG="ATM-$(echo "${ATM_VER}" | sed 's/\./_/g')"
ALMA_REL="$(sed 's/.*ALMA/ALMA/; s/ //g' "${DST}/ATM_VERSION")"
sed "s/getVersion();/getVersion() {return \"${ATM_VER}\";}/; \
     s/getTag();/getTag() {return \"${ATM_TAG}\";}/; \
     s/getALMARelease();/getALMARelease() {return \"${ALMA_REL}\";}/" \
    src/.template > "${DST}/src/ATMVersion.cpp"

{
  echo "path:   TelCalResults/Libraries/ATM"
  echo "commit: $(git log -1 --format=%H -- .)"
  echo "date:   $(git log -1 --format=%cI -- .)"
  echo "dirty:  $(git status --porcelain -- include src | grep -v _2024 | wc -l) modified file(s)"
} > "${DST}/TELCAL_SOURCE"

echo "Synced ATM ${ATM_VER} (${ALMA_REL}) from ${SRC} into ${DST}"
cat "${DST}/TELCAL_SOURCE"

# Reference outputs and input data of the ATM unit tests (used by tests/test_atm_unit.py)
TDST="${ROOT}/tests/atm"
rm -rf "${TDST}"
mkdir -p "${TDST}/ref" "${TDST}/data"
cp -p test/ref/*.ref "${TDST}/ref/"
for f in WVR_MAUNA_KEA/radiometer_data.dat MITO/MITO_AtmoPM_201007160400_ORIGINAL.dat T-INVERSION/invt.dat; do
  cp -p "test/$f" "${TDST}/data/$(basename "$f")"
done
echo "Synced ATM unit test references and data into ${TDST}"
