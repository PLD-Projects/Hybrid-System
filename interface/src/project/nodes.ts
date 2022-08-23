export const defaultNodes = [
    {
      id: 'grid',
      type: 'GridNode',
      data: {color:'gray'},
      position: { x: 0, y: 0 },
      style: {
        background: 'transparent',
        color: '#333',
        border: '1px solid transparent',
        height: 120,
        width: 70,
        borderRadius: '5px',
      },
    },
  
    {
      id: 'bat',
      type: 'BatNode',
      data: { },
      position: { x: 0, y: 200 },
      style: {
        background: 'transparent',
        color: '#333',
        border: '1px solid transparent',
        height: 75,
        width: 70,
        borderRadius: '5px',
      },
    },
    {
      id: 'inv',
      type: 'InvNode',
      data: {},
      position: { x: 200, y: 100 },
      style: {
        background: 'transparent',
        color: '#333',
        border: '1px solid transparent',
        height: 105,
        width: 70,
        borderRadius: '5px',
      },
    },
    {
      id: 'ts',
      type: 'TsNode',
      data: {},
      position: { x: 110, y: 25},
      style: {
        background: 'transparent',
        color: '#333',
        border: '1px solid',
        height: 70,
        width: 70,
        borderRadius: '5px',
      },
    },
    {
      id: 'load',
      type: 'LoadNode',
      data: {},
      position: { x: 250, y: 0},
      style: {
        background: 'transparent',
        color: '#333',
        border: '1px solid transparent',
        height: 50,
        width: 50,
        borderRadius: '5px',
      },
    },
  ];

export const defaultEdges = [
  { id: 'g2b', source: 'grid', target: 'bat',sourceHandle: 'a', type: 'step',},
  { id: 'b2i', source: 'bat', target: 'inv',type: 'step', },
  { id: 'i2t', source: 'inv', target: 'ts', targetHandle: 'b',type: 'step',},
  { id: 'g2t', source: 'grid', target: 'ts',sourceHandle: 'b', targetHandle: 'a',type: 'step',},
  { id: 't2l', source: 'ts', target: 'load',type: 'step',}
];

export const num2clr = {
  0: 'grey',
  1: '#ffcc00',
  2: 'green',
};
