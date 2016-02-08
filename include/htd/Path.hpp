/* 
 * File:   Path.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 * 
 * This file is part of htd.
 * 
 * htd is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free 
 * Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * htd is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public 
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HTD_HTD_PATH_HPP
#define	HTD_HTD_PATH_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IMutablePath.hpp>

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace htd
{
    class Path : public virtual htd::IMutablePath
    {
        public:
            Path(void);

            Path(const Path & original);

            Path(const htd::IPath & original);
            
            ~Path();
            
            std::size_t vertexCount(void) const HTD_OVERRIDE;

            std::size_t vertexCount(htd::vertex_t subPathRoot) const HTD_OVERRIDE;

            std::size_t edgeCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isEdge(htd::id_t edgeId) const HTD_OVERRIDE;

            bool isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            bool isEdge(const std::vector<htd::vertex_t> & elements) const HTD_OVERRIDE;

            bool isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::Collection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::vertex_t vertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isConnected(void) const HTD_OVERRIDE;
            
            bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const HTD_OVERRIDE;

            void copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> vertices(void) const HTD_OVERRIDE;

            std::size_t isolatedVertexCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const HTD_OVERRIDE;

            htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::edge_t> edges(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::edge_t> edges(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::edge_t & edgeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            const htd::edge_t & edgeAtPosition(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::Hyperedge> hyperedges(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::Hyperedge> hyperedges(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedge(htd::id_t edgeId) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t root(void) const HTD_OVERRIDE;

            bool isRoot(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t leafNodeCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> leafNodes(void) const HTD_OVERRIDE;

            htd::vertex_t leafNode(void) const HTD_OVERRIDE;

            htd::vertex_t leafNodeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isLeafNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t parent(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isParent(htd::vertex_t vertex, htd::vertex_t parent) const HTD_OVERRIDE;

            std::size_t childCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> children(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t child(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t child(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            bool isChild(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeSubpath(htd::vertex_t subpathRoot) HTD_OVERRIDE;

            htd::vertex_t insertRoot(void) HTD_OVERRIDE;
            
            void removeRoot(void) HTD_OVERRIDE;
            
            htd::vertex_t addChild(htd::vertex_t vertex) HTD_OVERRIDE;

            htd::vertex_t addParent(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeChild(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeChild(htd::vertex_t vertex, htd::vertex_t child) HTD_OVERRIDE;

            Path * clone(void) const HTD_OVERRIDE;

            Path & operator=(const Path & original);

            Path & operator=(const htd::IPath & original) HTD_OVERRIDE;

        protected:

            struct Node
            {
                htd::id_t id;

                htd::vertex_t parent;

                htd::vertex_t child;

                Node(htd::id_t id, htd::vertex_t parent) : id(id), parent(parent), child(htd::Vertex::UNKNOWN)
                {

                }
            };

            std::size_t size_;

            htd::vertex_t root_;

            htd::vertex_t next_vertex_;

            htd::vertex_container vertices_;

            std::unordered_map<htd::id_t, Node *> nodes_;

            void deleteNode(htd::Path::Node * node);
    };
}

#endif /* HTD_HTD_PATH_HPP */
