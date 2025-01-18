// import { Fragment } from "react"; <-- no need if use <> </>
// import { MouseEvent } from "react";
// {items [], heading: string }
interface Props {
  items: string[];
  heading: string;
  //(item: string) => void
  onSelectItem: (item: string) => void; //just like onClick
}
import { useState } from "react";

function ListGroup({ items, heading, onSelectItem }: Props) {
  //   let items = ["New York", "San Francisco", "Shanghai", "Paris", "Tokyo"];
  //hook
  const [selectedIndex, setSelectedIndex] = useState(-1);
  //   arr[0]; // variable(SelectedIndex)
  //   arr[1]; // updatedr function

  //   items = [];
  //   const message = return items.length === 0 ? <p>No item found</p> : null;
  //   const getMessage = () => {
  //     return items.length === 0 ? <p>No item found</p> : null;
  //   };

  //   if (items.length == 0)
  //     return (
  //       <>
  //         <h1>List</h1>   <-- BAD PRACTICE!! duplicate List
  //         <p>No Item Found</p>
  //       </>
  //     );

  //event handler
  //   const handleClick = (event: MouseEvent) => console.log(event);

  //PROPS => input passed to a component, similar to function args, immutable
  //STATE => Data managed by a component similar to local variables
  // both cause a re-render
  return (
    <>
      <h1>{heading}</h1>
      {items.length === 0 && <p>No item found</p>}
      <ul className="list-group">
        {items.map((item, index) => (
          <li
            className={
              selectedIndex === index
                ? "list-group-item active"
                : "list-group-item"
            }
            key={item}
            onClick={() => {
              setSelectedIndex(index);
              onSelectItem(item);
            }}
          >
            {item}
          </li> //Use item.id for real world applications
        ))}
      </ul>
    </>
  );
}

export default ListGroup;
