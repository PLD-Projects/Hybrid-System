export const defaultNodes = [
    {
      id: 'pv',
      type: 'PvNode',
      data: {color:'gray'},
      position: { x: 0, y: 109 },
      style: {
        background: 'transparent',
        color: '#333',
        border: '1px solid transparent',
        height: 50,
        width: 50,
        borderRadius: '5px',
      },
    },
    {
      id: 'grid',
      type: 'GridNode',
      data: {color:'gray'},
      position: { x: 200, y: 80 },
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
      id: 'ginv',
      type: 'GInvNode',
      data: {},
      position: { x: 100, y: 0 },
      style: {
        background: 'transparent',
        color: '#333',
        border: '1px solid transparent',
        height: 70,
        width: 70,
        borderRadius: '5px',
      },
    },
    {
      id: 'load',
      type: 'LoadNode',
      data: {},
      position: { x: 115, y: 109},
      style: {
        background: 'transparent',
        color: '#333',
        border: '1px solid transparent',
        height: 50,
        width: 40,
        borderRadius: '5px',
      },
    },
    {
      id: 'inv',
      type: 'InvNode',
      data: {},
      position: { x: 100, y: 200 },
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
      id: 'bat',
      type: 'BatNode',
      data: { },
      position: { x: 100, y: 350 },
      style: {
        background: 'transparent',
        color: '#333',
        border: '1px solid transparent',
        height: 75,
        width: 70,
        borderRadius: '5px',
      },
    },
  ];

export const defaultEdges = [
  { id: 'p2gi', source: 'pv', target: 'ginv',sourceHandle: 'a', targetHandle: 'a', type: 'step',},
  { id: 'p2i', source: 'pv', target: 'inv',sourceHandle: 'b', targetHandle: 'a', type: 'step',},

  { id: 'gi2g', source: 'ginv', target: 'grid',sourceHandle: 'b', targetHandle: 'a', type: 'step',},

  { id: 'g2l', source: 'grid', target: 'load',sourceHandle: 'b', targetHandle: 'a', type: 'step',},
  { id: 'g2i', source: 'grid', target: 'inv',sourceHandle: 'c', targetHandle: 'c', type: 'step',},

  { id: 'i2l', source: 'inv', target: 'load',sourceHandle: 'b', targetHandle: 'b', type: 'step',},
  { id: 'i2b', source: 'inv', target: 'bat',sourceHandle: 'd', targetHandle: 'a',type: 'step',},

  { id: 'b2i', source: 'bat', target: 'inv',sourceHandle: 'b', targetHandle: 'e', type: 'step', },
  // { id: 'i2t', source: 'inv', target: 'ts', targetHandle: 'b',type: 'step',},
  // { id: 'g2t', source: 'grid', target: 'ts',sourceHandle: 'b', targetHandle: 'a',type: 'step',},
  // { id: 't2l', source: 'ts', target: 'load',type: 'step',}
];

export const num2clr = {
  0: 'grey',
  1: '#ffcc00',
  2: 'green',
};
