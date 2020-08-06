// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file storage.hpp
 * @brief Implementation of the `storage` component handling persistent data across rounds.
 */

#ifndef FCPP_COMPONENT_STORAGE_H_
#define FCPP_COMPONENT_STORAGE_H_

#include <type_traits>

#include "lib/component/base.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {


//! @brief Namespace for all FCPP components.
namespace component {


//! @brief Namespace of tags to be used for initialising components.
namespace tags {
    //! @brief Declaration tag associating to a sequence of tags and types for storing persistent data.
    template <typename... Ts>
    struct tuple_store {};
}


/**
 * @brief Component modelling persistent data.
 *
 * <b>Declaration tags:</b>
 * - \ref tags::tuple_store defines a sequence of tags and types for storing persistent data (defaults to the empty sequence).
 */
template <typename... Ts>
struct storage {
    //! @brief Sequence of tags and types for storing persistent data.
    using tuple_store_type = common::option_types<tags::tuple_store, Ts...>;

    /**
     * @brief The actual component.
     * 
     * Component functionalities are added to those of the parent by inheritance at multiple levels: the whole component class inherits tag for static checks of correct composition, while `node` and `net` sub-classes inherit actual behaviour.
     * Further parametrisation with F enables <a href="https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern">CRTP</a> for static emulation of virtual calls.
     *
     * @param F The final composition of all components.
     * @param P The parent component to inherit from.
     */
    template <typename F, typename P>
    struct component : public P {
        DECLARE_COMPONENT(storage);

        //! @brief The local part of the component.
        class node : public P::node {
          public: // visible by net objects and the main program
            //! @brief Tuple type of the contents.
            using tuple_type = common::tagged_tuple_t<tuple_store_type>;

            /**
             * @brief Main constructor.
             *
             * @param n The corresponding net object.
             * @param t A `tagged_tuple` gathering initialisation values.
             */
            template <typename S, typename T>
            node(typename F::net& n, const common::tagged_tuple<S,T>& t) : P::node(n,t), m_storage(t) {}

            //! @brief Const access to stored data as tagged tuple.
            const tuple_type& storage_tuple() const {
                return m_storage;
            }

            /**
             * @brief Write access to stored data.
             *
             * @param T The tag corresponding to the data to be accessed.
             */
            template <typename T>
            typename tuple_type::template tag_type<T>& storage() {
                return common::get<T>(m_storage);
            }

            /**
             * @brief Const access to stored data.
             *
             * @param T The tag corresponding to the data to be accessed.
             */
            template <typename T>
            const typename tuple_type::template tag_type<T>& storage() const {
                return common::get<T>(m_storage);
            }

            /**
             * @brief Write access to stored data.
             *
             * @param T The tag corresponding to the data to be accessed.
             */
            template <typename T>
            typename tuple_type::template tag_type<T>& storage(T) {
                return common::get<T>(m_storage);
            }

            /**
             * @brief Const access to stored data.
             *
             * @param T The tag corresponding to the data to be accessed.
             */
            template <typename T>
            const typename tuple_type::template tag_type<T>& storage(T) const {
                return common::get<T>(m_storage);
            }

          private: // implementation details
            //! @brief The data storage.
            tuple_type m_storage;
        };

        //! @brief The global part of the component.
        using net = typename P::net;
    };
};


}


}

#endif // FCPP_COMPONENT_STORAGE_H_
