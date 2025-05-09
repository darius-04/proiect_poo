#ifndef TOPURI_H
#define TOPURI_H

#include <vector>
#include <memory>
#include "ObiectMuzical.h"
#include "Artist.h"
#include "Album.h"

class Topuri
{
public:
    static void topMelodii(const std::vector<std::shared_ptr<ObiectMuzical>>& obiecte, int topN = 5);
    static void topAlbume(const std::vector<std::shared_ptr<ObiectMuzical>>& obiecte, int topN = 5);
    static void topArtisti(const std::vector<std::shared_ptr<ObiectMuzical>>& obiecte, int topN = 3);
    static void topAlbumeDinAn(const std::vector<std::shared_ptr<ObiectMuzical>>& obiecte, int an);
};
#endif
